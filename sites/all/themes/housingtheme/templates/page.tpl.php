
      <div class="dashboard">
         <?php include('includes/left_menu.php'); ?>


         <div id="content-wrapper" class="content-wrapper">
            <!-- <nav class="navbar nav-theme">
              <div class="container-fluid">
                <span class="navbar-text">
                  Navbar text with an inline element
                </span>
              </div>
            </nav> -->
            <div class="main-content p-5 min-vh-100">
            
               <?php include('includes/breadcrumb.php'); ?>
               <div id="messages">
                  <div class="section clearfix">
                     <?php print $messages; ?>
                  </div>
               </div>
               <?php print render($page['content']); ?>
               
               <!-- <footer class="text-center p-3 mt-auto"> -->
                  <!-- <div class="after-login-footer row"> -->
                    <!-- <div class="row"> -->
                        <!-- <hr/>
                        <div class="col-md-8 copyright">
                        Copyright © All Rights Reserved
                        </div>
                        <div class="col-md-4" style="display:flex">
                           <div class="copyright">Designed & Developed By</div>
                           <div class="image-1"><img style="width:42%;"src="<?php //echo $base_root.$base_path ?>sites/all/themes/housingtheme/images/BILINGUAL FULL LENGTH VERSION  blue bg-01.PNG"></img></div>
                     </div>
                  </div> -->
                 <!--  </div> -->
               <!-- </footer> -->

               <footer class="text-center p-3 mt-auto"> 
                  <div class="after-login-footer row ftr-content">
                  <div class="row">
               <!--<div class="row ftr-content "> -->
                  <div class="col-md-7">
                     <p class="copyright">Copyright © All Rights Reserved</p>
                  </div>
                  <div class="col-md-5  text-end" style="color:#e9e1e1;">Designed & Developed by <a href="https://www.nic.in/" target="_blank">
                     <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/nic-logo2.jpg" alt="NIC - National Informatics Centre" title="NIC - National Informatics Centre" width="80"></a>
                  </div>
</div>
</div>
</footer>
               </div>
            </div>
         </div>
      </div>
