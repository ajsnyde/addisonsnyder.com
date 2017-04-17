<html>
	<?php
		include 'php/template.php';
        head('JqueryTest', 'JqueryTest');
	?>
    <body>
        <?php
          navBar();
        ?>
        <div class="container">
            <div class="row">
                <div class="col-lg-12" >
                    <div id="editor">
                        <p id="coordinates">LOADING...</p>
                        <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
                        <script type="text/javascript">
                            $(document).ready(function(){
                                $("body").mousemove(function(event){
                                document.getElementById("coordinates").innerHTML="Your mouse is at: ("+ event.pageX +"," + event.pageY+")";
                                });
                            });
                        </script>
                        <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/84/three.js"></script>
                        <script>
                            var camera, scene, renderer;
                            var mesh;
                            init();
                            animate();
                            function init() {
                                width = 600;
                                height = 600;
                                camera = new THREE.PerspectiveCamera( 50, width / height, 1, 1000 );
                                camera.position.z = 400;
                                scene = new THREE.Scene();
                                var texture = new THREE.TextureLoader().load( 'http://addisonsnyder.com/pics/URL_Fetcher.png' );

                               var materials = [
                                   new THREE.MeshBasicMaterial({
                                       map: texture
                                   }),
                                   new THREE.MeshBasicMaterial({
                                       map: texture
                                   }),
                                   new THREE.MeshBasicMaterial({
                                       map: texture
                                   }),
                                   new THREE.MeshBasicMaterial({
                                       map: texture
                                   }),
                                   new THREE.MeshBasicMaterial({
                                       map: texture
                                   }),
                                   new THREE.MeshBasicMaterial({
                                       map: texture
                                   })
                                ];
                                dice = new THREE.Mesh(
                                    new THREE.BoxGeometry( 200, 200, 200 ),
                                    new THREE.MultiMaterial( materials ) );
                                scene.add( dice );

                                renderer = new THREE.WebGLRenderer();
                                renderer.setPixelRatio( window.devicePixelRatio );
                                renderer.setSize( width, height );
                                document.getElementById("editor").appendChild( renderer.domElement );
                                //
                                window.addEventListener( 'resize', onWindowResize, false );
                                $("canvas").mousemove(function(e) {
                                    dice.rotation.x = e.pageX/100;
                                    dice.rotation.y = e.pageY/100;
                                })
                            }
                            function onWindowResize() {
                                camera.aspect = width / height;
                                camera.updateProjectionMatrix();
                                renderer.setSize( width, height );
                            }
                            function animate() {
                                requestAnimationFrame( animate );
                                renderer.render( scene, camera );
                            }
                            $(document).ready(function() {
                              $('img').click(function(e) {
                                var offset = $(this).offset();
                                alert((e.pageX - offset.left) + "," + (e.pageY - offset.top));
                              });
                            });
                        </script>
                    </div>
                </div>
                <img class="img" src="pics/Map1.PNG" alt="">
            </div>
        </div>
    </body>
</html>