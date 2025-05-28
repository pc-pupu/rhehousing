<section class="slider cus-responsive" style="overflow-x: hidden; overflow-y: inherit;">
    <div class="overlay-1"></div>
    <div class="overlay-2"></div>
    <div class="p-3 text-center position-absolute start-0 end-0">
        <div class="container">
            <a href="index.html">
                <div class="logo"><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/wb-logo.png" class="img-fluid# mh-100" /></div>
                <div class="logo-text">
                <h1 class="text-white fs-3">e-Allotment of Rental Housing Estate</h1>
                <h4 class="text-white fs-5">Housing Department | Government of West Bengal</h4>
                </div>
            </a> 
            <p class="lead">
                <b>Admin Sign</b> in to Continue
            </p>
            <div class="d-flex justify-content-center h-100 end-0 mb-6# mb-4">
                <div class="col-12 col-sm-10 col-md-8 col-lg-6 col-xl-5 col-xxl-4">
                    <div class="card border border-light-subtle rounded-4">
                        <div class="card-body p-3 p-md-3 p-xl-4 cus-login">                        
                        <?php print render($page['content']); ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>


    <?php include('includes/footer-content.php'); ?>

    
    
</section>

<div class="position-absolute collapse accessibility-panel" id="navbarToggleExternalContent">
    <div class="p-2">
        <ul class="font-panel">
            <li>
                <a href="#">
                <span><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/text-size.png"></span>
                <strong>Bigger Text</strong>
                </a>
            </li>
            <li>
                <a href="#">
                <span><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/text-size.png"></span>
                <strong>Small Text</strong>
                </a>
            </li>
            <li>
                <a href="#">
                <span><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/brightness-and-contrast.png"></span>
                <strong>Light-Dark</strong>
                </a>
            </li>
            <li>
                <a href="#">
                <span><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/reset.png"></span>
                <strong>Reset Settings</strong>
                </a>
            </li>
        </ul>
        
    </div>
</div>

<nav class="navbar accessibility position-absolute">
    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarToggleExternalContent" aria-controls="navbarToggleExternalContent" aria-expanded="false" aria-label="Toggle navigation">
    <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/accessability.png" class="img-fluid" />
    </button>
</nav>