<?php 
global $user, $user_role,$base_path,$base_root; 
?>
<div class="row">
    <!-- Done by Subham 20/06/2024 & 21/06/2024 -->
    <h4 class="mt-4">Welcome  <?= $user_info['applicantName'] ?></h4>
    <h6>Designation: <?= $user_info['applicantDesignation'] ?></h6>
    <h6>Mobile Number: <?= $user_info['mobileNo'] ?></h6>
    <h6>Email: <?= $user_info['email'] ?></h6>
    <?php if(isset($user_status) && $user_status == 'offer_letter_cancel'){ ?>
            <p style="color:red;">** Your offer letter has been cancelled due to non-acceptance within the 15-day timeline. Please contact your sub-divisonal Exec. Engineer within 5 days to request for offer letter extension; otherwise, your application will be considered cancelled. </p> <!-- Done by Subham 09-12-2024 -->
    <?php };
       
       
       if(isset($user_status) && $user_status == 'license_cancel'){ ?>
        <p style="color:red;">** The license has been canceled due to the failure to receive the possession letter within 15 days. Please contact your sub-divisonal Exec. Engineer within 5 days to request for license extension; otherwise, your application will be considered cancelled.</p>
    <?php }; ?> <!-- Done by debaleena 27-11-2024 -->
       
</div>
<div class="row">
   <div class="col-md-8">
      <div class="card">
         <div class="d-flex align-items-start row">
            <div class="col-md-7">
               <div class="card-body">
                  <h5 class="card-title text-primary mb-3">Welcome</h5>
                  <p class="mb-6">
                     You are awesome!!
                  </p>
               </div>
            </div>
            <div class="col-sm-5 text-center text-sm-left">
               <div class="card-body pb-0 px-0 px-md-6">
                  <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/man-with-laptop.PNG">
               </div>
            </div>
         </div>
      </div>
   </div>
</div>
<div class="card">
<div class="row mt-4">
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative">
         <span class="counter">200</span>
         <p>Allotment</p>
         <a href="allotment.html" class="badge rounded-pill text-bg-success">View Deatils</a>
         <!-- <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" /> -->
      </div>
   </div>
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative">
         <i class="fa fa-group"></i>
         <span class="counter">3275</span>
         <p>Floor Shifting</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Deatils</a>
         <!-- <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/floor-icon.png" class="position-absolute end-0 counter-box-icon top-0" /> -->
      </div>
   </div>
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative">
         <i class="fa  fa-shopping-cart"></i>
         <span class="counter">289</span>
         <p>Category Shifting</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Deatils</a>
         <!-- <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" /> -->
      </div>
   </div>
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative">
         <i class="fa  fa-user"></i>
         <span class="counter">1563</span>
         <p>New Licence</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Deatils</a>
         <!-- <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" /> -->
      </div>
   </div>
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative">
         <i class="fa  fa-user"></i>
         <span class="counter">1563</span>
         <p> Floor Shifting Licence</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Deatils</a>
         <!-- <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" /> -->
      </div>
   </div>
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative">
         <i class="fa  fa-user"></i>
         <span class="counter">1563</span>
         <p>Category Shifting Licence</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Deatils</a>
         <!-- <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" /> -->
      </div>
   </div>                
</div>
</div>
