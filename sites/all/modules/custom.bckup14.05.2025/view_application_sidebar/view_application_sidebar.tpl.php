<?php 
	global $user_role;

	$trail = menu_get_active_trail();
	//echo print_r($trail);
	// $path = $trail[(sizeof($trail)-1)]['link_path'];
    $path = isset($trail[count($trail)-1]['link_path']) ? $trail[count($trail)-1]['link_path'] : 'default_value'; // Done by Subham 12-02-2025
	/*echo '<br>';
	echo print_r($path);*/

?>
<ul class="menu">
	
	<?php /*?><li class="first leaf" style="border-bottom: none;"> 
		<?php echo l('Application of Registration List','application_registration_list') ?>
    </li><?php */?>

    <li class="first leaf" style="border-bottom: none;"> <a style="cursor:pointer;" class="toggle-menu <?php echo $path == 'view_application_list/%/%' ?'active':($path == 'view_application/%/%' ?'active':($path == 'application_detail/%' ?'active':''));?>"> Application List <span style="margin-left:10px;color:#00AEEF;"></span></a>
    
        <ul class="menu" style="display:<?php echo $path == 'view_application_list/%/%' ?'block':($path == 'view_application/%/%' ?'block':($path == 'application_detail/%' ?'block':'none'));?>;">

            <?php
                if($user_role == 11){
                    $new_status = 'applied';
                    $next_status_app = 'ddo_verified_1';
                    $next_status_rej = 'ddo_rejected_1';

                }else if($user_role == 10){
                    $new_status = 'ddo_verified_1';
                    $next_status_app = 'housing_sup_approved_1';
                    $next_status_rej = 'housing_sup_reject_1';
                }else if($user_role == 13){
                    $new_status = 'housing_sup_approved_1';
                    $next_status_app = 'housingapprover_approved_1';    //debaleena 04-09-2024
                    $next_status_rej = 'housingapprover_reject1';
                }else if($user_role == 6){
                    $new_status = 'allotted';
                    $next_status_app = 'housing_official_approved';
                    $next_status_rej = 'housing_official_reject';
                }
            



            ?>
        
            <li class="first leaf"> <?php echo l('New Application <span style="margin-left:10px;"></span>','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('new-apply').'/'.'action-list',array('html' => TRUE)) ?> </li>
            <li class="leaf"> <?php echo l('Verified List <span style="margin-left:10px;"></span>','view_application_list/'.encrypt_url($next_status_app).'/'.encrypt_url('new-apply').'/'.'verified-list',array('html' => TRUE)) ?> </li>
            <li class="last leaf"> <?php echo l('Rejected List <span style="margin-left:10px;"></span>','view_application_list/'.encrypt_url($next_status_rej).'/'.encrypt_url('new-apply').'/'.'reject-list',array('html' => TRUE)) ?> </li>
            
        </ul> 
    </li>

    <!---- 30-05-2024 start-------->
    <?php if($user_role == 10 || $user_role == 11){?> 
    <li class="first leaf" style="border-bottom: none;"> <a style="cursor:pointer;" class="toggle-menu <?php echo $path == 'view_application_list/%/%' ?'active':($path == 'view_application/%/%' ?'active':($path == 'application_detail/%' ?'active':''));?>"> Alloted Application List <span style="margin-left:10px;color:#00AEEF;"></span></a>
    
        <ul class="menu" style="display:<?php echo $path == 'view_application_list/%/%' ?'block':($path == 'view_application/%/%' ?'block':($path == 'application_detail/%' ?'block':'none'));?>;">

            <?php
                if($user_role == 11){//ddo
                    $new_status = 'applicant_acceptance';
                    $next_status_app = 'ddo_verified_2';
                    $next_status_rej = 'ddo_rejected_2';

                }else if($user_role == 10){// housing-supervisor
                    $new_status = 'ddo_verified_2';
                    $next_status_app = 'housing_sup_approved_2';
                    $next_status_rej = 'housing_sup_reject_2';
                }
            
            ?>
        
            <li class="first leaf"> <?php echo l('New Application <span style="margin-left:10px;"></span>','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('new-apply').'/'.'action-list',array('html' => TRUE)) ?> </li>
            <li class="leaf"> <?php echo l('Verified List <span style="margin-left:10px;"></span>','view_application_list/'.encrypt_url($next_status_app).'/'.encrypt_url('new-apply').'/'.'verified-list',array('html' => TRUE)) ?> </li>
            <li class="last leaf"> <?php echo l('Rejected List <span style="margin-left:10px;"></span>','view_application_list/'.encrypt_url($next_status_rej).'/'.encrypt_url('new-apply').'/'.'reject-list',array('html' => TRUE)) ?> </li>
            
        </ul> 
    </li>
    <?php } ?>
    <!---------end----------->
  
    <?php /*?><li class="first leaf" style="border-bottom: none;"> <a style="cursor:pointer;" class="toggle-menu <?php echo $path == 'view_waiting_list' ? 'active' : ($path == 'vacany_list' ? 'active' : ($path == 'allotment_list' ? 'active' : ($path == 'rhe_allotment' ? 'active' : ($path == 'flat_type_waiting_list' ? 'active' : ''))));?>"> RHE Allotment </a>
    
        <ul class="menu" style="display:<?php echo $path == 'view_waiting_list' ? 'block' : ($path == 'vacany_list' ? 'block' : ($path == 'allotment_list' ? 'block' : ($path == 'rhe_allotment' ? 'block' : ($path == 'flat_type_waiting_list' ? 'block' : 'none'))));?>;"><?php */?>
        
    <li class="first leaf" style="border-bottom: none;"> 
    <a style="cursor:pointer;" class="toggle-menu <?php echo $path == 'flat_type_waiting_list' ? 'active' : ($path == 'vacany_list' ? 'active' : ($path == 'flattype_applicant_vacancy' ? 'active' : ($path == 'allotment_list' ? 'active' : ($path == 'allotment_list_approve' ? 'active' : ($path == 'rhe_allotment' ? 'active' : '')))));?>"> RHE Allotment </a>
    
        <ul class="menu" style="display:<?php echo $path == 'flat_type_waiting_list' ? 'block' : ($path == 'vacany_list' ? 'block' : ($path == 'flattype_applicant_vacancy' ? 'block' : ($path == 'allotment_list' ? 'block' : ($path == 'allotment_list_approve' ? 'block' : ($path == 'rhe_allotment' ? 'block' : 'none')))));?>;">
        
           <?php /*?> <li class="first leaf"> <?php echo l('Combined Waiting List','view_waiting_list') ?> </li><?php */?>
           
            <li class="first leaf"> <?php echo l('Flat Type Wise Waiting List','flat_type_waiting_list') ?> </li>
            <li class="leaf"> <?php echo l('RHE Vacancy List','vacany_list') ?> </li>
            <!--<li class="leaf"> <?php /*?>//<?php echo l('Flat Type Wise Waiting Applicant and Flat Vacancy','flattype_applicant_vacancy') ?><?php */?> </li>-->
            
            <?php if($user_role == 9) { ?>
            	<li class="last leaf"> <?php echo l('Allotment List','allotment_list') ?> </li>
            <?php } else { ?>
            	<li class="leaf"> <?php echo l('Allotment List','allotment_list') ?> </li>
            <?php } ?>
            
           <?php 
             /*if($user_role != 9) { ?>
                <li class="leaf"> <?php echo l('Allotment List Approve','allotment_list_approve') ?> </li>
                <li class="last leaf"> <?php echo l('Allotment','rhe_allotment') ?> </li>
            <?php } */?> 

            <!-- debaleena -->
            <?php 
             if($user_role == 10) { ?>
                <li class="leaf"> <?php echo l('Allotment List Approve','allotment_list_approve') ?> </li>
                <li class="last leaf"> <?php echo l('Allotment','rhe_allotment') ?> </li>
            <?php } ?>

            <!-- end -->
            
        </ul>
    </li>
    
    <?php /*?><li class="first leaf" style="border-bottom: none;"> <a style="cursor:pointer;" class="toggle-menu <?php echo $path == 'vs_allotment' ? 'active' : ($path == 'cs_allotment' ? 'active' : ($path == 'cs_allotment_list' ? 'active' : ($path == 'vs_allotment_list' ? 'active' : '')));?>"> RHE Shifting Allotment </a>
    
        <ul class="menu" style="display:<?php echo $path == 'vs_allotment' ? 'block' : ($path == 'cs_allotment' ? 'block' : ($path == 'cs_allotment_list' ? 'block' : ($path == 'vs_allotment_list' ? 'block' : 'none')));?>;">
        
            <li class="first leaf"> <?php echo l('Generate Vertical Shifting Allotment','vs_allotment') ?> </li>
            <li class="leaf"> <?php echo l('Generate Category Shifting Allotment','cs_allotment') ?> </li>
            
            <li class="last leaf"> <?php echo l('VS Allotment List','vs_allotment_list') ?> </li>
            <li class="leaf"> <?php echo l('CS Allotment List','cs_allotment_list') ?> </li>
            
        </ul>
   	</li><?php */?>
    
    <!-- <li class="first leaf" style="border-bottom: none;"> <a style="cursor:pointer;" class="toggle-menu <?php //echo $path == 'generate_new_license' ? 'active' : ($path == 'generate_vs_licence' ? 'active' : ($path == 'generate_cs_licence' ? 'active' : ($path == 'licence_list' ? 'active' : ($path == 'rhewise_licensee_list' ? 'active' : ''))));?>"> RHE Licence </a>
        
        <ul class="menu" style="display:<?php //echo $path == 'generate_new_license' ? 'block' : ($path == 'generate_vs_licence' ? 'block' : ($path == 'generate_cs_licence' ? 'block' : ($path == 'licence_list' ? 'block' : ($path == 'rhewise_licensee_list' ? 'block' : 'none'))));?>;">
        
        <?php if($user_role == 6) { ?>
            <li class="first leaf"> <?php //echo l('Generate New Licence','generate_new_license') ?> </li>
        <?php } else { ?>
        	<li class="first leaf"> <?php //echo l('Download and Upload New Licence','generate_new_license') ?> </li>
        <?php } 
        
        	 if($user_role == 6) { ?>   
            <li class="leaf"> <?php //echo l('Generate Floor Shifting Licence','generate_vs_licence') ?> </li>
        <?php } else { ?>
        	<li class="leaf"> <?php //echo l('Download and Upload Floor Shifting Licence','generate_vs_licence') ?> </li>
        <?php } 
        
        	 if($user_role == 6) { ?>    
            <li class="leaf"> <?php //echo l('Generate Category Shifting Licence','generate_cs_licence') ?> </li>
         <?php } else { ?>
        	<li class="leaf"> <?php //echo l('Download and Upload Category Shifting Licence','generate_cs_licence') ?> </li>
         <?php } ?>
            
            <li class="leaf"> <?php //echo l('Licence Type Wise Licensee List','licence_list') ?> </li>
            <li class="last leaf"> <?php //echo l('RHE Wise Licensee List','rhewise_licensee_list') ?> </li>
            
        </ul>
   	</li> -->
 
</ul>
