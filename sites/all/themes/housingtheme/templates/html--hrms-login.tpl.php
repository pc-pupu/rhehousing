<section class="slider">
        <div class="overlay-1"></div>
        <div class="overlay-2"></div>
        
        <div class="p-5 text-center position-absolute start-0 end-0">
            <div class="container">
                <a href="index.html">
                    <div class="logo"><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/wb-logo.png" class="img-fluid" /></div>
                    <div class="logo-text">
                    <h1 class="text-white">e-Allotment of Rental Housing Estate</h1>
                    <h4 class="text-white">Housing Department | Government of West Bengal</h4>
                    </div>
                </a> 
                <p class="lead">
                    Search for a flat in any <b>Housing Estates</b>
                </p>
                <?php print render($page['content']); ?>
            </div>
        </div>


        <div class="position-fixed start-0 end-0 bottom-0 bg-dark">
        <div class="container">
            <div class="d-flex flex-wrap justify-content-between align-items-center p-3 my-3">
              <div class="col-md-2 d-flex align-items-center">
                <a href="#" class="mb-3 me-2 mb-md-0 text-decoration-none lh-1">
                  <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/nic_logo.png" class="img-fluid" alt="NIC logo" loading="lazy">
                </a>
               
              </div>
          
              <div class="col-md-10 justify-content-end list-unstyled d-flex">
                <span class="mb-3 mb-md-0 text-light">
                  <small>All contents of the this site are owned and maintained by Department of West Bengal. National Informatics Centre (NIC), will not be responsible for any loss to any person caused by inaccuracy in the information available on this Website.</small>
               </span>
              </div>
            </div>
            <p class="text-center text-body-secondary"> Copyright © All Rights Reserved</p>
        </div>
        </div>

        
        <footer class="text-center p-3">
            <div class="container-lg">
                <div class="row">
                    <div class="col-md-6 text-start">
                        <p class="copyright">Copyright © All Rights Reserved</p>
                    </div>
                    <div class="col-md-6 text-end">
                        <p>
                            <a href="https://silpasathi.wb.gov.in/faq">Contact</a> &nbsp;|&nbsp;
                            <a href="https://silpasathi.wb.gov.in/sitemap">Site Map</a> &nbsp;|&nbsp;
                            <a href="https://silpasathi.wb.gov.in/privacy-policy">Privacy Policy</a> &nbsp;|&nbsp;
                            <a href="https://silpasathi.wb.gov.in/disclaimer">Disclaimer</a></p>
                    </div>
                </div>
        </footer>
    </section>

    <div class="accessibility position-absolute"><img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/accessability.png" /></div>