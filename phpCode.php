<!DOCTYPE html>
<html lang="en">
    <?php
      include 'php/template.php';
      head('Addison Snyder - Portfolio', 'The following is my collection of (mostly) personal projects');
    ?>
  <body style="height: 100vh; padding-top: 0px;">
    <?php
    echo '<iframe src="/editor.php?file=php%2Ftemplate.php&lang=php" class="ifm" scrolling="no" seamless="seamless" height="100%" width="100%" style="border:none; overflow:scroll; overflow-y: hidden;" scrolling="no"></iframe>';
    ?>
  </body>
  <?php 
  loadJS();
?>
</html>