<?php 
global $user, $user_role,$base_path,$base_root;

?>

<div class="row">
   <div class="col-md-12">
      <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm row">
         <div class="col-md-9">
         <h4 class="title-lg">Welcome to e-Allotment of Rental Housing Estate</h4><br>
         <!--<h4 class="mt-4">Welcome  <?= $output['user_info']['applicantName'] ?></h4> -->
         <h6>Designation: <?= $output['user_info']['applicantDesignation'] ?></h6>
         <h6>Mobile Number: <?= $output['user_info']['mobileNo'] ?></h6>
         <h6>Email: <?= $output['user_info']['email'] ?></h6>
         <?php if(isset($output['user_status']) && $output['user_status'] == 'offer_letter_cancel'){ ?>
                  <p style="color:red;">** Your offer letter has been cancelled due to non-acceptance within the 15-day timeline. Please contact your sub-divisonal Exec. Engineer within 5 days to request for offer letter extension; otherwise, your application will be considered cancelled. </p> <!-- Done by Subham 09-12-2024 -->
         <?php };
      
            if(isset($output['user_status']) && $output['user_status'] == 'license_cancel'){ ?>
            <p style="color:red;">** The license has been cancelled due to the failure to receive the possession letter within 15 days. Please contact your sub-divisonal Exec. Engineer within 5 days to request for license extension; otherwise, your application will be considered cancelled.</p>
         <?php }; ?> <!-- Done by debaleena 27-11-2024 -->
         </div>
         <div class="col-md-3"><img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/dashboard-user.jpeg" style="border-radius: 50%;" /></div>
         <!-- <img src="<?php //echo $base_root.$base_path?>sites/all/themes/housingtheme/images/dashboard-user.jpeg" class="position-absolute# end-0# counter-box-icon top-0" /> -->
      </div>
   </div>
   <?php
         // print_r($output);die;
         $output['new-apply'] = isset($output['new-apply']) ? $output['new-apply'] : 0;
         $output['vs'] = isset($output['vs']) ? $output['vs'] : 0;
         $output['cs'] = isset($output['cs']) ? $output['cs'] : 0;

         $output['allotted-apply'] = isset($output['allotted-apply']) ? $output['allotted-apply'] : 0;
         $output['allotted-vs'] = isset($output['allotted-vs']) ? $output['allotted-vs'] : 0;
         $output['allotted-cs'] = isset($output['allotted-cs']) ? $output['allotted-cs'] : 0;
         $output['all-applications'] = isset($output['all-applications']) ? $output['all-applications'] : 0;
         $output['all-license'] = isset($output['all-license']) ? $output['all-license'] : 0;
         $output['all-exsting-occupant'] = isset($output['all-exsting-occupant']) ? $output['all-exsting-occupant'] : 0;
         $output['auto-cancellation'] = isset($output['auto-cancellation']) ? $output['auto-cancellation'] : 0;

   if($user_role == 11){ 
       // For DDO 
      $ddo_status = 'applied';
      $allotted_ddo_status = 'applicant_acceptance'; ?> 
   <div class="col-md-12">
      <div class="row">
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
               <span class="counter"><?php echo $output['new-apply'];  ?></span>
               <p>New Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($ddo_status).'/'.encrypt_url('new-apply').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['vs'];  ?></span>
               <p>Vertical Shifting Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($ddo_status).'/'.encrypt_url('vs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box3">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['cs'];  ?></span>
               <p>Category Shifting Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($ddo_status).'/'.encrypt_url('cs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-category.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-apply'] ?></span>
               <p>Allotted New Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_ddo_status).'/'.encrypt_url('new-apply').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-vs'] ?></span>
               <p>Allotted VS Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_ddo_status).'/'.encrypt_url('vs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box3">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-cs'] ?></span>
               <p>Allotted CS Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_ddo_status).'/'.encrypt_url('cs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-category.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
      </div>
   </div>
   <?php } ?>
   <?php if($user_role == 10){
      $osd_status = 'ddo_verified_1';
      $allotted_osd_status = 'ddo_verified_2'; // For Housing Supervisor ?> 
   <div class="col-md-12">
      <div class="row">
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
               <span class="counter"><?php echo $output['new-apply'];?></span>
               <p>New Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($osd_status).'/'.encrypt_url('new-apply').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['vs'];?></span>
               <p>Vertical Shifting Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($osd_status).'/'.encrypt_url('vs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box3">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['cs'];?></span>
               <p>Category Shifting Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($osd_status).'/'.encrypt_url('cs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-category.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-apply']; ?></span>
               <p>Allotted New Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_osd_status).'/'.encrypt_url('new-apply').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-vs']; ?></span>
               <p>Allotted VS Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_osd_status).'/'.encrypt_url('vs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box3">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-cs']; ?></span>
               <p>Allotted CS Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_osd_status).'/'.encrypt_url('cs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-category.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
      </div>
   </div>
   <?php } ?>
   <?php if($user_role == 7){ // For Sub-divison ?> 
   <!-- </Done by Subham bt. 30-12-2024> -->
   <div class="col-md-12">
      <div class="row">
         <div class="col-md-6 ">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1 w-100">
               <span class="counter"><?php echo $output['all-exsting-occupant']; ?></span>
               <p>Existing Occupant</p>
               <a href="<?php echo $base_root.$base_path.'view-occupant-list/'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-6 ">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2 w-100">
               <span class="counter"><?php echo $output['auto-cancellation']; ?></span>
               <p>Auto Cancelled Offer Letters / Licenses</p>
               <a href="<?php echo $base_root.$base_path.'auto-cancellation-list/'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
      </div>
   </div>
   <?php } ?>
   <?php if($user_role == 8){ // For Divison ?> 
   <!-- </Done by Subham bt. 31-12-2024> -->
   <div class="col-md-12">
      <div class="row">
         <div class="col-md-6 ">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1 w-100">
               <span class="counter"><?php echo $output['all-exsting-occupant']; ?></span>
               <p>Existing Occupant</p>
               <a href="<?php echo $base_root.$base_path.'view-occupant-list/'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
      </div>
   </div>
   <?php } ?>
   <?php if($user_role == 13){
      $approver_status = 'housing_sup_approved_1';
      $allotted_approver_status = 'housing_sup_approved_2';  // For Housing Approver ?> 
   <div class="col-md-12">
      <div class="row">
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
               <span class="counter"><?php echo $output['new-apply'] ?></span>
               <p>New Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($approver_status).'/'.encrypt_url('new-apply').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['vs'] ?></span>
               <p>Vertical Shifting Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($approver_status).'/'.encrypt_url('vs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box3">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['cs'] ?></span>
               <p>Category Shifting Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($approver_status).'/'.encrypt_url('cs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-category.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-apply'] ?></span>
               <p>Allotted New Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_approver_status).'/'.encrypt_url('new-apply').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-allotment.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box2">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-vs'] ?></span>
               <p>Allotted VS Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_approver_status).'/'.encrypt_url('vs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-floor.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
         <div class="col-md-4">
            <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box3">
               <!-- <i class="fa fa-group"></i> -->
               <span class="counter"><?php echo $output['allotted-cs'] ?></span>
               <p>Allotted CS Application</p>
               <a href="<?php echo $base_root.$base_path.'view_application_list/'.encrypt_url($allotted_approver_status).'/'.encrypt_url('cs').'/'.'action-list'?>" class="badge rounded-pill text-bg-success">View Details</a>
               <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-category.png"
                  class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
            </div>
         </div>
      </div>
   </div>
   <?php } ?>
   <?php if($user_role == 6 ){ //For Housing Official ?>
   <div class="col-md-12">
      <div class="row">
         <div class="col-md-4">
            <div class="row">
               <div class="col-md-12">
                  <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box1">
                     <!-- <i class="fa fa-group"></i> -->
                     <span class="counter"><?php echo $output['all-applications']?></span>
                     <p>All Pending Application</p>
                     <a href="<?php echo $base_root.$base_path.'allotment_list_approve/'?>" class="badge rounded-pill text-bg-success">View Details</a>
                     <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme//images/icon-allotment.png"
                     class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
                  </div>
               </div>
            </div>
            <div class="row">
               <div class="col-md-12">
                  <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm color-box4">
                     <!-- <i class="fa  fa-shopping-cart"></i> -->
                     <span class="counter"><?php echo $output['all-license'] ?></span>
                     <p>Pending License Generation</p>
                     <a href="<?php echo $base_root.$base_path.'generate-license/'?>" class="badge rounded-pill text-bg-success">View Details</a>
                     <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/icon-licence.png"
                     class="position-absolute end-0 counter-box-icon top-0 mt-2 me-2" />
                  </div>
               </div>
            </div>
         </div>
         <div class="col-md-8">
            <div class="row">
               <!-- <h4 class="mt-4">Flat Type Wise Waiting List</h4> -->
               <div class="table-responsive rounded counter-box shadow-sm p-3">
                  <table class="table table-list table-striped table-hover table-bordered">
                     <thead>
                        <tr class="table-primary">
                           <th>Flat Type</th>
                           <th>No. of Waitlisted Applications
                           <a href="<?php echo $base_root.$base_path.'flat_type_waiting_list/'?>" class="badge rounded-pill text-bg-success">View Details</a>
                           </th>
                        </tr>
                     </thead>
                     <tbody>
                        <tr>
                           <td><b>A</b></td>
                           <?php $data=flat_type_wise_waiting_detail(1);?>
                           <td><?php echo count($data);?></td> 
                        </tr>
                        <tr>
                           <td><b>B</b></td>
                           <?php $data=flat_type_wise_waiting_detail(2);?>
                           <td><?php echo count($data);?></td>  
                        </tr>
                        <tr>
                           <td><b>C</b></td>
                           <?php $data=flat_type_wise_waiting_detail(3);?>
                           <td><?php echo count($data);?></td>   
                        </tr>
                        <tr>
                           <td><b>D</b></td>
                           <?php $data=flat_type_wise_waiting_detail(4);?>
                           <td><?php echo count($data);?></td>   
                        </tr>
                        <tr>
                           <td><b>A+</b></td>
                           <?php $data=flat_type_wise_waiting_detail(5);?>
                           <td><?php echo count($data);?></td>  
                        </tr>
                     </tbody>
               </table>
               </div>
            </div>
         </div>
      </div>
   </div>
   <?php } ?>
   <!-- <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm">
         <i class="fa  fa-user"></i>
         <span class="counter">1563</span>
         <p> Floor Shifting Licence</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Details</a>
         <img src="./images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" />
      </div>
   </div>
   <div class="col-md-3">
      <div class="counter-box p-3 rounded mb-3 position-relative shadow-sm">
         <i class="fa  fa-user"></i>
         <span class="counter">1563</span>
         <p>Category Shifting Licence</p>
         <a href="#" class="badge rounded-pill text-bg-success">View Details</a>
         <img src="./images/allotment-icon.png" class="position-absolute end-0 counter-box-icon top-0" />
      </div>
   </div> -->
</div>
<?php
   //foreach ($output['fetch_cuurent_status'] as $data) {
   // print_r($output['fetch_current_status']->short_code);die;
   // $redirect_link = '<a href="'.$base_root.$base_path.'allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.$output['fetch_current_status']->allotment_no.'">Click Here</a>';
   // echo $redirect_link;die;

    
      // Done by dg 26-12-2024
      // if(strpos($output['fetch_current_status']->allotment_no, 'NAL') !== false)
      // {
      //    $redirect_link = '<a href="'.$base_root.$base_path.'allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.encrypt_url($output['fetch_current_status']->allotment_no).'"> Download Now</a>';

      // }else if(strpos($output['fetch_current_status']->allotment_no, 'VSAL') !== false)
      // {
      //    $redirect_link = '<a href="'.$base_root.$base_path.'vs_allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.encrypt_url($output['fetch_current_status']->allotment_no).'"> Download Now</a>';

         
      // }else if(strpos($output['fetch_current_status']->allotment_no, 'CSAL') !== false)
      // {
      //    $redirect_link = '<a href="'.$base_root.$base_path.'cs_allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.encrypt_url($output['fetch_current_status']->allotment_no).'"> Download Now</a>';

      // }
      
     
   
if ($user_role == 4 || $user_role == 5){ // For Applicant/Occupant 

     // Done by Subham 26-12-2024
     $allotment_no = isset($output['fetch_current_status']->allotment_no) ? $output['fetch_current_status']->allotment_no : '';

     // Done by Subham 27-12-2024
     $redirect_link = strpos($allotment_no, 'NAL') !== false ? '<a href="'.$base_root.$base_path.'allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.encrypt_url($allotment_no).'"> Download Now</a>': (strpos($allotment_no, 'VSAL') !== false ? '<a href="'.$base_root.$base_path.'vs_allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.encrypt_url($allotment_no).'"> Download Now</a>': (strpos($allotment_no, 'CSAL') !== false ? '<a href="'.$base_root.$base_path.'cs_allotment_detail_pdf_gen/'.encrypt_url($output['fetch_current_status']->online_application_id).'/'.encrypt_url($allotment_no).'"> Download Now</a>': null));
     //echo $allotment_no;die;


    // Done by Subham 26-12-2024
    $license_no = isset($output['fetch_license_status']->online_application_id) ? $output['fetch_license_status']->online_application_id : '';
   
    // Done by dg 26-12-2024
    $redirect_link_license = '<a href="'.$base_root.$base_path.'download_licence_pdf/'.encrypt_url($license_no).'/"> Download Now</a>';
?>


<!-- <div class="col-md-12"> -->
   <div class="row">
      <h4 class="mt-4">Application List</h4>
      <div class="col-md-9">
         <div class="table-responsive rounded counter-box shadow-sm p-3">
            <?php if (!empty($output['all-application-data'])){ ?>
               <table class="table table-list table-striped table-hover table-bordered">
                  <thead>
                     <tr class="table-primary">
                        <th>Name</th>
                        <th>Application Number</th>
                        <th>Date of Application</th>
                        <th>Status of Application</th>
                        <!-- <th>Flat Type</th> -->
                        <!-- <th>View</th> -->
                     </tr>
                  </thead>
                  <tbody>
                     <tr> 
                        <?php foreach ($output['all-application-data'] as $application):  // Done by Subham 24-12-2024?>
                        <td><b><?= $application->applicant_name ?></b></td>
                        <td><?= $application->application_no ?></td>
                        <td><?= !empty($application->date_of_application) ? date('d-m-Y', strtotime($application->date_of_application)) : 'N/A' ?></td>
                        <td><?= $application->status_description ?></td>
                        <!-- <td>Physically Handicaped or Serious Illness</td> -->
                        <!-- <td><a href="#"
                              class="btn btn-outline-primary btn-sm px-5 rounded-pill fw-bolder">View</a></td> -->
                     </tr>
                     <?php endforeach; ?>
                     <!-- <tr>
                        <td><b>Debaleena</b></td>
                        <td>NA-15042024-3273</td>
                        <td>15/04/2024</td>
                        <td>D</td> -->
                        <!-- <td>Physically Handicaped or Serious Illness</td> -->
                        <!-- <td><a href="#"
                              class="btn btn-outline-primary btn-sm px-5 rounded-pill fw-bolder">View</a></td> -->
                        
                     <!-- </tr>
                     <tr>
                        <td><b>Debaleena</b></td>
                        <td>NA-15042024-3273</td>
                        <td>15/04/2024</td>
                        <td>D</td> -->
                        <!-- <td>Physically Handicaped or Serious Illness</td> -->
                        <!-- <td><a href="#"
                              class="btn btn-outline-primary btn-sm px-5 rounded-pill fw-bolder">View</a></td> -->
                        <!-- <td>
                           <span class="badge text-bg-danger rounded">
                              <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor"
                                 class="bi bi-x-circle" viewBox="0 0 16 16">
                                 <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14m0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16" />
                                 <path
                                    d="M4.646 4.646a.5.5 0 0 1 .708 0L8 7.293l2.646-2.647a.5.5 0 0 1 .708.708L8.707 8l2.647 2.646a.5.5 0 0 1-.708.708L8 8.707l-2.646 2.647a.5.5 0 0 1-.708-.708L7.293 8 4.646 5.354a.5.5 0 0 1 0-.708" />
                              </svg>
                           </span>
                           <span class="badge text-bg-success rounded">
                              <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor"
                                 class="bi bi-check2-circle" viewBox="0 0 16 16">
                                 <path
                                    d="M2.5 8a5.5 5.5 0 0 1 8.25-4.764.5.5 0 0 0 .5-.866A6.5 6.5 0 1 0 14.5 8a.5.5 0 0 0-1 0 5.5 5.5 0 1 1-11 0" />
                                 <path
                                    d="M15.354 3.354a.5.5 0 0 0-.708-.708L8 9.293 5.354 6.646a.5.5 0 1 0-.708.708l3 3a.5.5 0 0 0 .708 0z" />
                              </svg>
                           </span>
                        </td> -->
                     <!-- </tr> -->
                     <?php }else{  // Done by Subham 03-01-2025?>
                        <tr>No Application Data Found</tr> 
                     <?php } ?>
                  </tbody>
               </table>
            <?php if (!empty($output['all-application-data'])){ ?>
            <nav aria-label="Page navigation example">
               <ul class="pagination justify-content-end pagination-sm">
                  <li class="page-item disabled">
                     <a class="page-link">Previous</a>
                  </li>
                  <li class="page-item"><a class="page-link" href="#">1</a></li>
                  <li class="page-item"><a class="page-link" href="#">2</a></li>
                  <li class="page-item"><a class="page-link" href="#">3</a></li>
                  <li class="page-item">
                     <a class="page-link" href="#">Next</a>
                  </li>
               </ul>
            </nav>
            <?php }?>
         </div>
      </div>
      <div class="col-md-3">
         <div class="card h-100 notification-box">
            <div class="card-body">
               <div id="carouselExampleCaptions" class="carousel slide h-100" data-bs-ride="carousel">
                  <div class="carousel-indicators">
                     <button type="button" data-bs-target="#carouselExampleCaptions" data-bs-slide-to="0"
                        class="active" aria-current="true" aria-label="Slide 1"></button>
                     <button type="button" data-bs-target="#carouselExampleCaptions" data-bs-slide-to="1"
                        aria-label="Slide 2"></button>
                  </div>
                  <div class="carousel-inner text-center">
                 
                     <div class="carousel-item active p-3">
                        <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/notification.png" class="w-75" />
                        <!-- <h5>Latest Notification</h5> -->
                        <?php if($allotment_no != ''){?>
                           <p style="color:red; font-family: Arial, sans-serif; font-size: 16px;">1. Your Offer Letter is generated, download from here!</p>
                           <i class="fa fa-download" style="margin-right: 4px; color:blue;"><?php echo $redirect_link; // Done by dg 26-12-2024 ?></i>
                        <?php }else{  ?>
                           <p style="color:red; font-family: Arial, sans-serif; font-size: 16px;">No Latest Notifications</p>
                        <?php } ?>   
                       
                     </div>
                  

                    
                     <div class="carousel-item p-3">
                        <img src="<?php echo $base_root.$base_path?>sites/all/themes/housingtheme/images/notification.png" class="w-75" />
                        <!-- <h5>Latest Notification</h5> -->
                        <?php if($license_no != ''){?> 
                           <p style="color:red; font-family: Arial, sans-serif; font-size: 16px;">2. Your License is generated, download from here!</p><i class="fa fa-download" style="margin-right: 4px; color:blue;"><?php echo $redirect_link_license;  // Done by dg 26-12-2024?></i>
                        <?php }else{ ?>
                           <p style="color:red; font-family: Arial, sans-serif; font-size: 16px;">No Latest Notifications</p>
                        <?php } ?>
                        <!-- <button type="button" class="btn btn-secondary btn-sm rounded-pill">Download
                           List</button> -->
                     </div>
                  
                  </div>
               </div>
            </div>
         </div>
      </div>
   </div>
<!-- </div> -->
<?php } ?>
<div class="row mt-5">
   <!-- <div class="col-md-3">
      <div class="card">
         <img src="<?php// echo $base_root.$base_path?>sites/all/themes/housingtheme/images/bela_housing_3.jpeg" class="card-img-top w-100" alt="Bela Housing Complex">
         <div class="card-body">
            <h5 class="card-title">Card title</h5>
            <p class="card-text text-justify">All the Lorem Ipsum generators on the Internet tend to repeat
               predefined
               chunks as necessary, making this the first true generator on the Internet.</p>
            <a href="#" class="btn btn-primary rounded-pill">Go somewhere</a>
         </div>
      </div>
   </div> -->
   <!-- <div class="col-md-3">
      <div class="card">
         <img src="<?php// echo $base_root.$base_path?>sites/all/themes/housingtheme/images/bela_housing_2.jpeg" class="card-img-top w-100" alt="Bela Housing Complex">
         <div class="card-body">
            <h5 class="card-title">Card title</h5>
            <p class="card-text">All the Lorem Ipsum generators on the Internet tend to repeat predefined
               chunks as necessary, making this the first true generator on the Internet.</p>
            <a href="#" class="btn btn-primary rounded-pill">Go somewhere</a>
         </div>
      </div>
   </div> -->
   <!-- <div class="col-md-3">
      <div class="card">
         <img src="<?php //echo $base_root.$base_path?>sites/all/themes/housingtheme/images/bela_housing_3.jpeg" class="card-img-top w-100" alt="Bela Housing Complex">
         <div class="card-body">
            <h5 class="card-title">Card title</h5>
            <p class="card-text">All the Lorem Ipsum generators on the Internet tend to repeat predefined
               chunks as necessary, making this the first true generator on the Internet.</p>
            <a href="#" class="btn btn-primary rounded-pill">Go somewhere</a>
         </div>
      </div>
   </div> -->
   <!-- <div class="col-md-3">
      <div class="card">
         <img src="<?php //echo $base_root.$base_path?>sites/all/themes/housingtheme/images/bela_housing_2.jpeg" class="card-img-top w-100" alt="Bela Housing Complex">
         <div class="card-body">
            <h5 class="card-title">Card title</h5>
            <p class="card-text">All the Lorem Ipsum generators on the Internet tend to repeat predefined
               chunks as necessary, making this the first true generator on the Internet.</p>
            <a href="#" class="btn btn-primary rounded-pill">Go somewhere</a>
         </div>
      </div>
   </div> -->
</div>
<!-- <hr/> -->
            <!-- <div class="row ftr-content">
               <div class="col-md-7">
                  <p class="copyright">Copyright © All Rights Reserved</p>
               </div>
               <div class="col-md-5 text-end">Designed & Developed by <a href="https://www.nic.in/" target="_blank"><img
                        src="images/nic-logo2.jpg" alt="NIC - National Informatics Centre"
                        title="NIC - National Informatics Centre" width="80"></a></div>
            </div> -->