<!DOCTYPE html>
<html lang="en">
	<?php
include 'php/template.php';
head('Addison Snyder - Portfolio', 'The following is my collection of (mostly) personal projects');
?>



  <body>
  <?php
// define variables and set to empty values
$name = $email = $textArea = $password = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
  $name = test_input($_POST["name"]);
  $email = test_input($_POST["email"]);
  $password = test_input($_POST["password"]);
  $textArea = test_input($_POST["textArea"]);
  echo '<p>'.$email.'</p>';
    	$db2 = new SQLite3('form.db');
    	$stmt = $db2->prepare("INSERT INTO TestForm  VALUES (?,?,?,?)");
    	$stmt->bindParam(1, $email);
    	$stmt->bindParam(2, $name);
    	$stmt->bindParam(3, $textArea);
    	$stmt->bindParam(4, $password);
    	$stmt->execute();
}
?>
	<?php
navBar();
?>
  <div class="container">
    <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>" method="post">
      <div class="form-group">
        <label for="exampleInputEmail1">Email address</label>
        <input type="email" class="form-control <?php echo $password; ?>" id="exampleInputEmail1" name="email" aria-describedby="emailHelp" placeholder="Enter email">
        <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
      </div>
      <div class="form-group">
        <label for="exampleInputPassword1">Password</label>
        <input type="password" class="form-control <?php echo $password; ?>" id="exampleInputPassword1" name="password" placeholder="Password">
      </div>
      <div class="form-group">
        <label for="exampleTextarea">Example textarea</label>
        <textarea class="form-control <?php echo $password; ?>" id="exampleTextarea" name="textArea" rows="3"></textarea>
      </div>
    <button type="submit" class="btn btn-primary">Submit</button>
  </form>
<?php
footer();
?>
    </div>
  </body>
  <?php
loadJS();
?>
</html>