<?php 
global $base_path,$base_root; 

?>
<section class="slider cus-responsive">
        <div class="overlay-1"></div>
        <div class="overlay-2"></div>
        <?php echo l('Admin Login','user/login',array('html' => true, 'attributes' => array('class'=>array('admin-login position-absolute end-0 mx-4 mt-5')))); ?>
        
        <div class="p-5 text-center position-absolute start-0 end-0">
            <div class="container">
                <a href="<?= $base_root ?>">
                    <div class="logo"><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/wb-logo.png" class="img-fluid" /></div>
                    <div class="logo-text">
                    <h1 class="text-white">e-Allotment of Rental Housing Estate</h1>
                    <h4 class="text-white">Housing Department | Government of West Bengal</h4>
                    </div>
                </a>
                <div id="messages">
                  <div class="section clearfix">
                     <?php print $messages; ?>
                  </div>
               </div>
                <?php print render($page['content']); ?>
            </div>
        </div>

        <?php include('includes/footer-content.php'); ?>
        
    </section>

    <div class="accessibility position-absolute"><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/accessability.png" /></div>