<?php
try {
  $GLOBALS['db'] = new SQLite3('db/db.db');
} catch (Exception $e) {
  die();
}
$GLOBALS['author'] = 'Addison Snyder';

function head($title, $description)
  {
  echo ('
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="' . $description . '">
    <meta name="author" content="' . $GLOBALS['author'] . '">
    <title>' . $title . '</title>
    <link REL="shortcut icon" href="pics/favicon.png" TYPE="image/x-icon">
    <link href="css/1-col-portfolio.css" rel="stylesheet">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
    <link href="css/custom.css" rel="stylesheet">
    <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
    <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>');
  }

  function footer()
  {
  echo ('<footer>
        <div class="row">
          <div class="col-lg-12">
            <p><a href="javascript:var%20s%20=%20document.createElement(&quot;script&quot;);s.type=&quot;text/javascript&quot;;document.body.appendChild(s);s.src=&quot;/js/asteroids.js&quot;;void(0);"><span id="kickass" metadot-translation="" class="ng-isolate-scope">Destroy this Site (not my code)</span></a></p>
            <p>Hosted using <a href="https://hub.docker.com/_/php/">php:7.1.0-apache</a> Docker image through <a href="https://portal.cycle.io">Cycle.io</a></p>
            <p>Copyright <span style="color: #f92672">&copy</span> </span><strong>' . date("Y") . '</strong> Addison Snyder </p>
            <!-- This Website was first created on 10/7/15 -->
          </div>
        </div>
      </footer>');
  }

  function loadJS()
  {
  echo ('
    <script src="http://code.jquery.com/jquery-3.1.1.min.js" integrity="sha256-hVVnYaiADRTO2PzUGmuLJr8BLUSjGIZsDYGmIJLv2b8=" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>');
  }

function navbar()
  {
  echo ('<nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
          <span class="sr-only">Toggle navigation</span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand'.(trim(strval(parse_url($_SERVER['REQUEST_URI'])['path'])) === '/index.php'?' active':'').'" href="index.php">Addison Snyder</a>
        </div>
        <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
          <ul class="nav navbar-nav">
          ');
  $results = $GLOBALS['db']->query('SELECT * FROM navItems ORDER BY displayOrder');
  while ($row = $results->fetchArray())
    {
    // display individual items in the navbar (active logic is super-messy but works..)
    echo ('<li '.(((strcmp(trim(strval(parse_url($_SERVER['REQUEST_URI'])['path'])),trim('/'.strval($row['link']))))) === 0?'class = "active"':'').'><a href="'.strval($row['link']).'">' . $row['displayText'] . '</a></li>');
    }
  echo ('</ul>
          <ul class="nav navbar-nav navbar-right">
            <li>
              <a href="Mailto:ajsnyde@bgsu.edu">ajsnyde@bgsu.edu</a>
            </li>
          </ul>
        </div>
      </div>
    </nav>');
  }

function portfolio()
  {
  echo ('
        <div class="row">
        <div class="col-lg-12">
          <h1 class="page-header">Portfolio
            <small>Recent Projects</small>
          </h1>
        </div>
      </div>
      ');
  // DB should be read-only, so I'm not too worried about injection attacks here. Absolute worst case, somebody could crash my server or limit availability.
  if (!isset($_GET['whereClause'])) $_GET['whereClause'] = '';
  $db = new SQLite3('db/db.db');
  $query2 = 'SELECT COUNT(*) AS numResults FROM posts ' . $_GET['whereClause'];
  $GLOBALS['numResults'] = ($db->query($query2))->fetchArray() ['numResults'];
  if (!isset($_GET['numberPerPage'])) $_GET['numberPerPage'] = 5;
  if (!isset($_GET['order'])) $_GET['order'] = 'DESC';
  if (!isset($_GET['pageNum']) || $_GET['pageNum'] < 1) $_GET['pageNum'] = 1;
  if ($_GET['pageNum'] > ($GLOBALS['numResults'] / $_GET['numberPerPage'])) $_GET['pageNum'] = ceil($GLOBALS['numResults'] / $_GET['numberPerPage']);
  $query = 'SELECT * FROM posts ' . $_GET['whereClause'] . ' ORDER BY date ' . $_GET['order'] . ' LIMIT ' . $_GET['numberPerPage'] . ' OFFSET ' . ($_GET['numberPerPage'] * ($_GET['pageNum'] - 1));
  $results = $db->query($query);
  while ($row = $results->fetchArray())
    {
    $out = '<div class="row">';
    if ($row['leftColSize'] != 0 && $row['leftHtml'] != '') $out = $out . '<div class="col-md-' . $row['leftColSize'] . '">' . $row['leftHtml'] . '</div>';
    if ($row['rightColSize'] != 0 && $row['rightHtml'] != '') $out = $out . '<div class="col-md-' . $row['rightColSize'] . '">' . '<h3>' . $row['title'] . ' <small>' . date("m-d-y", strtotime($row['date'])) . '</small></h3><h4>' . $row['subtitle'] . '</h4>' . $row['rightHtml'] . '</div>';
    $out = $out . '</div><hr>';
    echo ($out);
    }
  echo ('
          <div class="row text-center">
            <div class="col-lg-12">
              <ul class="pagination">
                <li><a href="' . 'index.php?' . http_build_query(array_merge($_GET, Array(
    'pageNum' => strval($_GET['pageNum'] - 1)
  ))) . '">&laquo;</a></li>');
  for ($i = 1; $i < ($GLOBALS['numResults'] / $_GET['numberPerPage']) + 1; $i++) if ($i != $_GET['pageNum']) echo ('<li><a href="' . 'index.php?' . http_build_query(array_merge($_GET, Array(
    'pageNum' => strval($i)
  ))) . '">' . $i . '</a></li>');
    else echo ('<li class="active"><a href="' . 'index.php?' . http_build_query(array_merge($_GET, Array(
    'pageNum' => strval($i)
  ))) . '">' . $i . '</a></li>');
  echo ('<li><a href="' . 'index.php?' . http_build_query(array_merge($_GET, Array(
    'pageNum' => strval($_GET['pageNum'] + 1)
  ))) . '">&raquo;</a></li>
              </ul>
            </div>
          </div>
          <hr>
          ');
  }

function about(){
  echo ('<div class="row">
            <div class="col-md-4 col-sm-3 col-xs-3">
                <img class="img-responsive" src="pics/portraitsmall.jpg" alt="">
            </div>

            <div class="col-md-8 col-sm-9 col-xs-12">
                <h3>Stay awhile and listen!</h3>
                <p>Hello and welcome to my website! I am a BGSU Computer Science student looking into getting a job. Please note that this site is far from completion, and that I started working on it on <b>10/7/15</b>. I have just started working with <strong>html/css/javascript</strong>, and so most of what you see is just a Frankenstein of Bootstrap templates. That is good too, as I am not looking to work on front-end web dev for the long-term. Overall, I am looking for a productive outlet for my skills and abilities.</p>
                <h4>More About Me <small>(Extra Features)</small></h4>
                </ul>
                    <li>Comes with <strong>38 sq. ft.</strong> of whiteboard</li>
                    <li>Solid working ethic</li>
                    <li>Enthusiastic: <i>out-of-the-box functionality!</i></li>
                </ul>
            </div>

        </div>
        <hr>
');
}
function contact(){
  echo ('<div class="row">
            <div class="col-md-4">
                <img class="img-responsive" src="pics/portraitsmall.jpg" alt="">
            </div>
            <div class="col-md-8">
                <h2>Contact Information</h3>
                <ul>
                    <li>Addison Snyder</li>
                    <li><a href="Mailto:ajsnyde@bgsu.edu">ajsnyde@bgsu.edu</a></li>
                    <li><a href="Mailto:addison@addisonsnyder.com">addison@addisonsnyder.com</a></li>
                    <li>Living in Bowling Green, OH</li>
                    <li>Please <a href="Mailto:ajsnyde@bgsu.edu?Subject=Phone%20Number">email</a> for phone number</li>
                </ul>
            </div>
        </div>
        <hr>');
}
?>