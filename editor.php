<html>
	<?php
		include 'php/template.php';
        head($_GET['file'], 'Editor for the following file:'.$_GET['file']);
	?>
    <body>
        <?php
          navBar();
        ?>
        <style type="text/css" media="screen">
            #editor { 
                position: absolute;
                top: 0;
                right: 0;
                bottom: 0;
                left: 0;
            }
        </style>
        <div class="container" style="width: 100%;">
            <div class="row">
                <div class="col-lg-12" style="height: 100%;">
                    <div id="editor">Loading file...</div>
                </div>
            </div>
        </div>
        <script src="/js/ace/src-min/ace.js" type="text/javascript" charset="utf-8"></script>
        <script>
            var editor = ace.edit("editor");
            editor.setTheme("ace/theme/monokai");
            editor.getSession().setMode(<?php echo '"ace/mode/'.($_GET['lang']?:'java').'"'?>);
            editor.setShowPrintMargin(false);

            <?php
            if (isset($_GET['file'])){
	            $components = parse_url($_GET['file']);
	            #load via PHP if file is local to server, load via js otherwise
	            if(empty($components['host']) || strcasecmp($components['host'], $_SERVER['HTTP_HOST']))
	                echo('editor.setValue('.json_encode(file_get_contents($_GET['file'])).')');
	            else{
	                echo('
	            Online file functionality
	            var client = new XMLHttpRequest();
	            client.open("GET", '.'"'.$_GET['file'].'");
	            client.onreadystatechange = function() {
	                editor.setValue(client.responseText);
	            }
	            client.send();');
	            }
        	} else
        		echo('editor.setValue()');
            ?>
        </script>
    </body>
</html>nt.send();');
	            }
        	}
            ?>
        </script>
    </body>
</html>