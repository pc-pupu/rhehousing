<?php include('includes/header.php'); ?>


<div id="carouselExampleIndicators" class="carousel slide" data-bs-ride="true">
    <div class="carousel-indicators">
        <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
        <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="1" aria-label="Slide 2"></button>
        <button type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide-to="2" aria-label="Slide 3"></button>
    </div>
    <div class="carousel-inner">
        <div class="carousel-item active">
        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/banner-02.jpg" class="d-block w-100" alt="...">
        </div>
        <div class="carousel-item">
        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/banner-03.jpg" class="d-block w-100" alt="...">
        </div>
        <div class="carousel-item">
        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/banner-01.jpg" class="d-block w-100" alt="...">
        </div>
    </div>
    <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="prev">
        <span class="carousel-control-prev-icon" aria-hidden="true"></span>
        <span class="visually-hidden">Previous</span>
    </button>
    <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="next">
        <span class="carousel-control-next-icon" aria-hidden="true"></span>
        <span class="visually-hidden">Next</span>
    </button>
</div>
<div class="container-fluid important-info">
    <div id="carouselExampleDark" class="carousel carousel-dark slide">
        <!-- <div class="carousel-indicators">
            <button type="button" data-bs-target="#carouselExampleDark" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
            <button type="button" data-bs-target="#carouselExampleDark" data-bs-slide-to="1" aria-label="Slide 2"></button>
            <button type="button" data-bs-target="#carouselExampleDark" data-bs-slide-to="2" aria-label="Slide 3"></button>
        </div> -->
        <div class="carousel-inner important-info-carousel-inner">
            <div class="carousel-item active info" data-bs-interval="10000">
                <!-- <img src="..." class="d-block w-100" alt="..."> -->

                <!-- Instead of image, div with style and min-height -->
                 <!-- <div class="info"> -->
                    <div class="carousel-caption1 d-block">
                        <h5 class="important-info-heading">Important Announcements</h5>
                        <p class="important-info-text">Some representative placeholder content for the first slide.</p>
                    </div>
                <!-- </div> -->
                <!-- end of div style min-height: 140px; -->
            </div>
            <div class="carousel-item" data-bs-interval="2000">
                <!-- Instead of image, div with style and min-height -->
                 <!-- <div class="info"> -->
                    <div class="carousel-caption1 d-block">
                        <h5 class="important-info-heading">Important Announcements</h5>
                        <p class="important-info-text">Some representative placeholder content for the second slide.</p>
                    </div>
                <!-- </div> -->
                <!-- end of div style min-height: 140px; -->
            </div>
            <div class="carousel-item">
                <!-- Instead of image, div with style and min-height -->
                 <!-- <div class="info"> -->
                    <div class="carousel-caption1 d-block">
                        <h5 class="important-info-heading">Important Announcements</h5>
                        <p class="important-info-text">Some representative placeholder content for the third slide.</p>
                    </div>
                <!-- </div> -->
                <!-- end of div style min-height: 140px; -->
            </div>
        </div>
        <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleDark" data-bs-slide="prev">
            <span class="carousel-control-prev-icon" aria-hidden="true"></span>
            <span class="visually-hidden"></span>
        </button>
        <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleDark" data-bs-slide="next">
            <span class="carousel-control-next-icon" aria-hidden="true"></span>
            <span class="visually-hidden"></span>
        </button>
    </div>
</div><!-- end .container -->

<!-- Welcome section start -->
<!-- <section class="welcome-bg#">
<div class="container">
    <div class="row">
        <div class="col-md-12 bg-white rounded shadow# p-4">
            <div class="row">
                <div class="col-md-7">
                    <h1 class="text-center text-primary">Welcome to Housing Department</h1>
                    <h4 class="text-center text-success">Government of West Bengal</h4>
                    <p class="text-center text-secondary">মানুষের জীবনধারণের জন্য সংবিধানস্বীকৃত নূন্যতম তিনটি
                        প্রয়োজনের মধ্যে
                        অন্ন আর বস্ত্রের
                        পরেই যেটি আসে, তা হ'ল <span class="text-dark">বাসস্থান</span> । পশ্চিমবঙ্গ সরকারের আবাসন
                        বিভাগের তাই মূল লক্ষ্যই হ'ল,
                        রাজ্যের প্রতিটি মানুষের জন্য সুনিশ্চিত করা অন্তত একটি<br>
                        <span class="text-center text-lg fs-1 text-dark">'মাথার উপর ছাদ'</span>
                    </p>
                    <h5 class="text-secondary">For human livelihood, ‘Shelter’ is the third basic minimum need,
                        after ‘Food’ and
                        ‘Clothes’, as recognised by the Indian Constitution.</h5>
                    <p class="text-justify text-secondary">The Department of Housing undertakes various
                        activities mainly
                        relating to the framing
                        and implementation of various Social Housing schemes through the Directorate of Housing
                        and West Bengal Housing Board.Besides, there are two other Directorates under the
                        administrative control of the Housing Department viz. the Estate Directorate and the
                        Brick Production Directorate,responsible mainly for the management of different
                        Government Housing Estates, and, Production & supply of quality bricks at reasonable
                        price respectively.</p>
                </div>
                <div class="col-md-5"><img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/swiper-2.jpg" alt="" class="w-100 rounded"></div>
            </div>
        </div>
    </div>
</div>
</section> -->
<!-- Welcome section end -->
<!--counter section starts------>
<div class="count">
    <div class="container">
        <div class="row">
            <div class="count_box col-md-3 poppins-semibold">
                <div class="count_box_text">
                    <span class="count_no"><strong>23</strong></span>
                    <span class="count_label">Districts</span>
                </div>
            </div>
            <div class="count_box col-md-3  poppins-semibold">
                <div class="count_box_text">
                    <span class="count_no"><strong>35</strong></span>
                    <span class="count_label">Rental Housing Estates</span>
                </div>
            </div>
            <div class="count_box col-md-3  poppins-semibold">
                <div class="count_box_text">
                    <span class="count_no"><strong>1906</strong></span>
                    <span class="count_label">Total Blocks</span>
                </div>
            </div>
            <div class="count_box col-md-3  poppins-semibold">
                <div class="count_box_text">
                    <span class="count_no"><strong>13800</strong></span>
                    <span class="count_label">Total Flats</span>
                </div>
            </div>
        </div>
    </div>
</div>
<!---counter section ends--->
<!---- middle 1 section starts---->
<section class="mb-8">
    <div class="services small_pb">
        <div class="container-lg">
            <div class="row justify-content-center">
                <div class="col-xl-9 col-lg-9">
                    <div class="text-center animation animated fadeInUp" data-animation="fadeInUp" data-animation-delay="0.01s" style="animation-delay: 0.01s; opacity: 1;">
                        <div class="heading_s1 text-center mt-5">
                            <h1 class="poppins-regular">e-Allotment of Rental Housing Estates</h1>                      
                            <h3 class="poppins-light">Efficient and Transparent Housing Allocation for Government Employees</h3>                      
                        </div>
                        <!-- <p>Single Window Services can be accessed through an EODB-Online Single Window Portal using IT-enabled devices which includes desktop PCs and laptops.Later, this facility will also be available on tablets and smartphones.</p> -->
                        
                    </div>
                </div>
            </div>
            <div class="row allot mt-5">
                <div class="col-lg-4 col-md-6">
                    <a href="#" class="allot-btn-change">
                        <div class="icon_box icon_box_style1 animation animated fadeInUp" data-animation="fadeInUp" data-animation-delay="0.03s" style="animation-delay: 0.03s; opacity: 1;">
                            <div class="box_icon mb-3">
                            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" fill="currentColor" class="bi bi-envelope-paper" viewBox="0 0 16 16">
                                <path d="M4 0a2 2 0 0 0-2 2v1.133l-.941.502A2 2 0 0 0 0 5.4V14a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V5.4a2 2 0 0 0-1.059-1.765L14 3.133V2a2 2 0 0 0-2-2zm10 4.267.47.25A1 1 0 0 1 15 5.4v.817l-1 .6zm-1 3.15-3.75 2.25L8 8.917l-1.25.75L3 7.417V2a1 1 0 0 1 1-1h8a1 1 0 0 1 1 1zm-11-.6-1-.6V5.4a1 1 0 0 1 .53-.882L2 4.267zm13 .566v5.734l-4.778-2.867zm-.035 6.88A1 1 0 0 1 14 15H2a1 1 0 0 1-.965-.738L8 10.083zM1 13.116V7.383l4.778 2.867L1 13.117Z"/>
                            </svg>
                            </div>
                            <div class="intro_desc">
                                <h5 class="poppins-semibold">Application for Allotment</h5>
                                <p class="poppins-regular ">Allows employees of the GoWB to request housing accommodations</p>
                            </div>
                        </div>
                    </a>
                </div>
                <div class="col-lg-4 col-md-6">
                    <a href="#" class="allot-btn-change">
                        <div class="icon_box icon_box_style1 animation animated fadeInUp" data-animation="fadeInUp" data-animation-delay="0.05s" style="animation-delay: 0.05s; opacity: 1;">
                            <div class="box_icon mb-3">
                            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" fill="currentColor" class="bi bi-house-gear-fill" viewBox="0 0 16 16">
                                <path d="M7.293 1.5a1 1 0 0 1 1.414 0L11 3.793V2.5a.5.5 0 0 1 .5-.5h1a.5.5 0 0 1 .5.5v3.293l2.354 2.353a.5.5 0 0 1-.708.708L8 2.207 1.354 8.854a.5.5 0 1 1-.708-.708z"/>
                                <path d="M11.07 9.047a1.5 1.5 0 0 0-1.742.26l-.02.021a1.5 1.5 0 0 0-.261 1.742 1.5 1.5 0 0 0 0 2.86 1.5 1.5 0 0 0-.12 1.07H3.5A1.5 1.5 0 0 1 2 13.5V9.293l6-6 4.724 4.724a1.5 1.5 0 0 0-1.654 1.03"/>
                                <path d="m13.158 9.608-.043-.148c-.181-.613-1.049-.613-1.23 0l-.043.148a.64.64 0 0 1-.921.382l-.136-.074c-.561-.306-1.175.308-.87.869l.075.136a.64.64 0 0 1-.382.92l-.148.045c-.613.18-.613 1.048 0 1.229l.148.043a.64.64 0 0 1 .382.921l-.074.136c-.306.561.308 1.175.869.87l.136-.075a.64.64 0 0 1 .92.382l.045.149c.18.612 1.048.612 1.229 0l.043-.15a.64.64 0 0 1 .921-.38l.136.074c.561.305 1.175-.309.87-.87l-.075-.136a.64.64 0 0 1 .382-.92l.149-.044c.612-.181.612-1.049 0-1.23l-.15-.043a.64.64 0 0 1-.38-.921l.074-.136c.305-.561-.309-1.175-.87-.87l-.136.075a.64.64 0 0 1-.92-.382ZM12.5 14a1.5 1.5 0 1 1 0-3 1.5 1.5 0 0 1 0 3"/>
                            </svg>
                            </div>
                            <div class="intro_desc">
                                <h5 class="poppins-semibold">Online Allotment Process</h5>
                                <p class="poppins-light ">The online allotment process for flats with application, verification, and digital allocation</p>
                            </div>
                        </div>
                    </a>
                </div>

                <div class="col-lg-4 col-md-6 box-active">
                    <a href="#" class="allot-btn-change">
                        <div class="icon_box icon_box_style1 animation animated fadeInUp" data-animation="fadeInUp" data-animation-delay="0.02s" style="animation-delay: 0.02s; opacity: 1;">
                            
                            <div class="box_icon mb-3">
                            <svg xmlns="http://www.w3.org/2000/svg" width="40" height="40" fill="currentColor" class="bi bi-award" viewBox="0 0 16 16">
                                <path d="M9.669.864 8 0 6.331.864l-1.858.282-.842 1.68-1.337 1.32L2.6 6l-.306 1.854 1.337 1.32.842 1.68 1.858.282L8 12l1.669-.864 1.858-.282.842-1.68 1.337-1.32L13.4 6l.306-1.854-1.337-1.32-.842-1.68zm1.196 1.193.684 1.365 1.086 1.072L12.387 6l.248 1.506-1.086 1.072-.684 1.365-1.51.229L8 10.874l-1.355-.702-1.51-.229-.684-1.365-1.086-1.072L3.614 6l-.25-1.506 1.087-1.072.684-1.365 1.51-.229L8 1.126l1.356.702z"/>
                                <path d="M4 11.794V16l4-1 4 1v-4.206l-2.018.306L8 13.126 6.018 12.1z"/>
                            </svg>
                            </div>
                            <div class="intro_desc">
                                <h5 class="poppins-semibold">Issuance of License with QR Code</h5>
                                <p class="poppins-light ">Applicants receive a license with a QR code</p>
                            </div>
                        </div>
                    </a>
                </div>
            </div>
        </div>
    </div>
</section>
<!---middle 1 section ends-------->
<!-- middle 2 section starts--->
<section class="mb-8 mid-section">
    <div class="services small_pb">
        <div class="container-lg">
            <div class="row justify-content-center">
                <div class="col-xl-9 col-lg-9">
                    <div class="text-center animation animated fadeInUp" data-animation="fadeInUp" data-animation-delay="0.01s" style="animation-delay: 0.01s; opacity: 1;">
                        <div class="heading_s1 text-center mt-5">
                            <h1 class="poppins-extralight mb-4 abt-dept-heading">Government Residential Accommodation</h1>                
                            <h3 class="poppins-light mb-5">Housing Department administers the allotment of  Government Residential Accommodation
                            </h3>                      
                        </div>
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="col-md-6 abt-dept">
                    <p class="poppins-light ">The Department of Housing undertakes various activities mainly relating to the framing and implementation of various Social Housing schemes through the Directorate of Housing and West Bengal Housing Board.Besides, there are two other Directorates under the administrative control of the Housing Department viz. the Estate Directorate and the Brick Production Directorate,responsible mainly for the management of different Government Housing Estates, and, Production & supply of quality bricks at reasonable price respectively.</p>
                </div>
                <div class="col-md-6">
                   <div class="abt-img"><img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/rhe-flat.jpg"></div>
                </div>
            </div>
        </div>
    </div>
</section>


<!-- middle 2 section ends--->
<!-- Services section start -->
<!-- <section class="services-bg">
<div class="container">
    <div class="row">
        <div class="col-md-3 hme-services-title">
            <h1>Our<br> <strong>Services</strong></h1>
        </div>
        <div class="col-md-9 p-4 d-flex justify-content-center w-100#">
            <div class="multi-carousel" data-mdb-multi-carousel-init="" data-mdb-interval="2000">
                <div class="multi-carousel-inner">
                    <div class="multi-carousel-item">
                        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/pathasathi.jpg" alt="e-Services" class="w-100">
                    </div>
                    <div class="multi-carousel-item">
                        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/BSK-Logo.png" alt="Winter Landscape" class="w-100">
                    </div>
                    <div class="multi-carousel-item">
                        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/egiye-bangla.jpg" alt="Analytic Report" class="w-100">
                    </div>
                    <div class="multi-carousel-item">
                        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/wb-tourism-logo.png" alt="Winter Landscape" class="w-100">
                    </div>
                    <div class="multi-carousel-item">
                        <img src="<?= $base_root.$base_path ?>sites/all/themes/outertheme/images/wb-sabujsree.jpg" alt="Payment of BOCWW CESS" class="w-100">
                    </div>
                </div>
                <button class="carousel-control-prev" type="button" tabindex="0" data-mdb-slide="prev">
                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                </button>
                <button class="carousel-control-next" type="button" tabindex="0" data-mdb-slide="next">
                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                </button>
            </div>
        </div>
    </div>
</div>
</section> -->
<!-- Services section end -->


<?php include('includes/footer.php'); ?>