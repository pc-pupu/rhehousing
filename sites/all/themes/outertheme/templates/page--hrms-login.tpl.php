<?php global $base_path, $base_root; ?>

<section class="slider hrms-login-bg">   
    <div class="p-5 text-center position-absolute start-0 end-0 ">
        <div class="container">
            <a href="index.html">
                <div class="logo"><img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/wb-logo.png" class="img-fluid" /></div>
                <div class="logo-text services">
                <h1 class=" poppins-regular">e-Allotment of Rental Housing Estate</h1>
                <h4 class="poppins-medium abt-dept-heading">Housing Department | Government of West Bengal</h4>
                </div>
            </a> 
            <!-- <p class="lead">
                Search for a flat in any <b>Housing Estates</b>
            </p> -->
            <?php print render($page['content']); ?>
        </div>
    </div>
</section>