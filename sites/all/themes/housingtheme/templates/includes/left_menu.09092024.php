<?php 
global $user, $user_role,$base_path,$base_root; 


?>
<div class="sidebar d-flex flex-column p-3" >
    <a href="<?= $base_root.$base_path ?>" class="d-flex flex-column align-items-center mb-5 text-center">
        <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/wb-logo.png"  class="img-fluid" alt="e-Allotment of Rental Housing Estate">
        <div class="dashboard-logo">
            <div class="fs-5 fw-semibold lh-1">e-Allotment of Rental Housing Estate</div>
            <small>Housing Department <br/> Government of West Bengal</small>
        </div>
    </a>
    <ul class="nav nav-pills flex-column mb-auto">
        <li class="nav-item">
            <a href="<?= $base_root.$base_path.'dashboard' ?>" class="nav-link active#">
                <i class="fa fa-tachometer" aria-hidden="true"></i>
                Dashboard
            </a>
        </li>

       <?php if($user_role == 10 || $user_role == 6){ ?>
        <li class="nav-item">
            <a href="<?= $base_root.$base_path.'application_status_check' ?>" class="nav-link active#">
                <i class="fa fa-search" aria-hidden="true"></i>
                Search Application Details
            </a>
        </li>
        <?php }?>


        <?php
            if($user_role == 10 || $user_role == 11 || $user_role == 6 || $user_role == 13){
                if($user_role == 11){
                    $new_status = 'applied';
                    $next_status_app = 'ddo_verified_1';
                    $next_status_rej = 'ddo_rejected_1';

                }else if($user_role == 10){
                    $new_status = 'ddo_verified_1';
                    $next_status_app = 'housing_sup_approved_1';
                    $next_status_rej = 'housing_sup_reject_1';
                }else if($user_role == 13){  //added by debaleena 04-09-2024
                    $new_status = 'housing_sup_approved_1';
                    $next_status_app = 'housingapprover_approved_1';
                    $next_status_rej = 'housing_approver_reject_1';
                }else if($user_role == 6){
                    $new_status = 'allotted';
                    $next_status_app = 'housing_official_approved';
                    $next_status_rej = 'housing_official_reject';
                }
        ?>

        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <i class="fa fa-user-circle-o" aria-hidden="true"></i> New Application <i class="fa fa-angle-down fa-lg float-end mt-1" aria-hidden="true"></i>
                </svg>
            </a>
            <!--sd start 20-06-2024---->
            <ul class="submenu collapse">
                <li class=""><?= l('<i class="fa fa-clipboard" aria-hidden="true"></i> New Allotment','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('new-apply').'/'.'action-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?>            
                </li>

                <li class=""><?= l('<i class="fa fa-retweet" aria-hidden="true"></i> Vertical Shifting','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('vs').'/'.'action-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>

                <li class=""><?= l('<i class="fa fa-check-square-o" aria-hidden="true"></i> Category Shifting','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('cs').'/'.'action-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
            <!--sd end 20-06-2024---->
        </li>
        <?php
            }
            if($user_role == 10 || $user_role == 11){
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
        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
            <i class="fa fa-file-text-o" aria-hidden="true"></i> Allotted Application  
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                 <li class=""><?= l('<i class="fa fa-clipboard" aria-hidden="true"></i> New Allotment','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('new-apply').'/'.'action-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?>            
                </li>

                <li class=""><?= l('<i class="fa fa-retweet" aria-hidden="true"></i> Vertical Shifting','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('vs').'/'.'action-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>

                <li class=""><?= l('<i class="fa fa-check-square-o" aria-hidden="true"></i> Category Shifting','view_application_list/'.encrypt_url($new_status).'/'.encrypt_url('cs').'/'.'action-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li>
        
        <?php        
            }
            if($user_role == 4 || $user_role == 5){
        ?>
        <!--sd start 20-06-2024---->
        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-file-earmark-person-fill" viewBox="0 0 16 16">
                <path d="M9.293 0H4a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h8a2 2 0 0 0 2-2V4.707A1 1 0 0 0 13.707 4L10 .293A1 1 0 0 0 9.293 0M9.5 3.5v-2l3 3h-2a1 1 0 0 1-1-1M11 8a3 3 0 1 1-6 0 3 3 0 0 1 6 0m2 5.755V14a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1v-.245S4 12 8 12s5 1.755 5 1.755"/>
                </svg>
                Online Application  
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('New Allotment','new-apply',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Vertical Shifting','vs',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Category Shifting','cs',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li>
        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-file-earmark-person-fill" viewBox="0 0 16 16">
                <path d="M9.293 0H4a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h8a2 2 0 0 0 2-2V4.707A1 1 0 0 0 13.707 4L10 .293A1 1 0 0 0 9.293 0M9.5 3.5v-2l3 3h-2a1 1 0 0 1-1-1M11 8a3 3 0 1 1-6 0 3 3 0 0 1 6 0m2 5.755V14a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1v-.245S4 12 8 12s5 1.755 5 1.755"/>
                </svg>
                Status
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('Application Status','application_status',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Wait List Status','waiting_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li>
        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-file-earmark-person-fill" viewBox="0 0 16 16">
                <path d="M9.293 0H4a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h8a2 2 0 0 0 2-2V4.707A1 1 0 0 0 13.707 4L10 .293A1 1 0 0 0 9.293 0M9.5 3.5v-2l3 3h-2a1 1 0 0 1-1-1M11 8a3 3 0 1 1-6 0 3 3 0 0 1 6 0m2 5.755V14a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1v-.245S4 12 8 12s5 1.755 5 1.755"/>
                </svg>
                Allotment Details
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('New Allotment','view_allotment_details',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Vertical Shifting','view_vs_allotment_details',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                 <li class=""><?= l('Category Shifting','view_cs_allotment_details',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li>
        <!-- <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-file-earmark-person-fill" viewBox="0 0 16 16">
                <path d="M9.293 0H4a2 2 0 0 0-2 2v12a2 2 0 0 0 2 2h8a2 2 0 0 0 2-2V4.707A1 1 0 0 0 13.707 4L10 .293A1 1 0 0 0 9.293 0M9.5 3.5v-2l3 3h-2a1 1 0 0 1-1-1M11 8a3 3 0 1 1-6 0 3 3 0 0 1 6 0m2 5.755V14a1 1 0 0 1-1 1H4a1 1 0 0 1-1-1v-.245S4 12 8 12s5 1.755 5 1.755"/>
                </svg>
                License
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">

            </ul>
        </li> -->

         <!--sd end 20-06-2024---->            
        <?php
            }
            //sd start 20-06-2024
            if($user_role == 6){   //10 into 6 changed by debaleena 09-09-2024
        ?>

            <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <i class="fa fa-pie-chart" aria-hidden="true"></i> Allotment  
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('Run Allotment','rhe_allotment',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Flat Type Wise Waiting List','flat_type_waiting_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Vacancy List','vacany_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Allotment List','allotment_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li>
        <!------------------------27-08-2024 start-------------------------------->
        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
                <i class="fa fa-pie-chart" aria-hidden="true"></i> License  
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('Generate License','generate-license',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('View Generated Licenses','view-generated-license',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li>
        <!-----------------------27-08-2024 end----------------------------->

        <?php
            }
            if($user_role == 6){
        ?>
        <!-- <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
            <i class="fa fa-pie-chart" aria-hidden="true"></i> Allotment  
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('Approve Allotment','allotment_list_approve',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li> -->
                <!-- <li class=""><?= l('Flat Type Wise Waiting List','flat_type_waiting_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Vacancy List','vacany_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Allotment List','allotment_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            </ul>
        </li> --> 
        <li class="nav-item has-submenu">
            <a class="nav-link" href="#">
            <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-database-add" viewBox="0 0 16 16">
                <path d="M12.5 16a3.5 3.5 0 1 0 0-7 3.5 3.5 0 0 0 0 7m.5-5v1h1a.5.5 0 0 1 0 1h-1v1a.5.5 0 0 1-1 0v-1h-1a.5.5 0 0 1 0-1h1v-1a.5.5 0 0 1 1 0"/>
                <path d="M12.096 6.223A5 5 0 0 0 13 5.698V7c0 .289-.213.654-.753 1.007a4.5 4.5 0 0 1 1.753.25V4c0-1.007-.875-1.755-1.904-2.223C11.022 1.289 9.573 1 8 1s-3.022.289-4.096.777C2.875 2.245 2 2.993 2 4v9c0 1.007.875 1.755 1.904 2.223C4.978 15.71 6.427 16 8 16c.536 0 1.058-.034 1.555-.097a4.5 4.5 0 0 1-.813-.927Q8.378 15 8 15c-1.464 0-2.766-.27-3.682-.687C3.356 13.875 3 13.373 3 13v-1.302c.271.202.58.378.904.525C4.978 12.71 6.427 13 8 13h.027a4.6 4.6 0 0 1 0-1H8c-1.464 0-2.766-.27-3.682-.687C3.356 10.875 3 10.373 3 10V8.698c.271.202.58.378.904.525C4.978 9.71 6.427 10 8 10q.393 0 .774-.024a4.5 4.5 0 0 1 1.102-1.132C9.298 8.944 8.666 9 8 9c-1.464 0-2.766-.27-3.682-.687C3.356 7.875 3 7.373 3 7V5.698c.271.202.58.378.904.525C4.978 6.711 6.427 7 8 7s3.022-.289 4.096-.777M3 4c0-.374.356-.875 1.318-1.313C5.234 2.271 6.536 2 8 2s2.766.27 3.682.687C12.644 3.125 13 3.627 13 4c0 .374-.356.875-1.318 1.313C10.766 5.729 9.464 6 8 6s-2.766-.27-3.682-.687C3.356 4.875 3 4.373 3 4"/>
            </svg>
                Legacy Data  
                <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
                </svg>
            </a>
            <ul class="submenu collapse">
                <li class=""><?= l('Legacy Applicant Entry','existing_applicant_entry',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
                <li class=""><?= l('Legacy Applicant List','view-legacy-applicant-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>

            </ul>
        </li>
        <li class="nav-item">
            <?= l('<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-building-gear" viewBox="0 0 16 16">
            <path d="M2 1a1 1 0 0 1 1-1h10a1 1 0 0 1 1 1v6.5a.5.5 0 0 1-1 0V1H3v14h3v-2.5a.5.5 0 0 1 .5-.5H8v4H3a1 1 0 0 1-1-1z"/>
            <path d="M4.5 2a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm3 0a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm3 0a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm-6 3a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm3 0a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm3 0a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm-6 3a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm3 0a.5.5 0 0 0-.5.5v1a.5.5 0 0 0 .5.5h1a.5.5 0 0 0 .5-.5v-1a.5.5 0 0 0-.5-.5zm4.386 1.46c.18-.613 1.048-.613 1.229 0l.043.148a.64.64 0 0 0 .921.382l.136-.074c.561-.306 1.175.308.87.869l-.075.136a.64.64 0 0 0 .382.92l.149.045c.612.18.612 1.048 0 1.229l-.15.043a.64.64 0 0 0-.38.921l.074.136c.305.561-.309 1.175-.87.87l-.136-.075a.64.64 0 0 0-.92.382l-.045.149c-.18.612-1.048.612-1.229 0l-.043-.15a.64.64 0 0 0-.921-.38l-.136.074c-.561.305-1.175-.309-.87-.87l.075-.136a.64.64 0 0 0-.382-.92l-.148-.045c-.613-.18-.613-1.048 0-1.229l.148-.043a.64.64 0 0 0 .382-.921l-.074-.136c-.306-.561.308-1.175.869-.87l.136.075a.64.64 0 0 0 .92-.382zM14 12.5a1.5 1.5 0 1 0-3 0 1.5 1.5 0 0 0 3 0"/>
            </svg> Treasury Estate Mapping','estate-treasury-selection',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?>
        </li>
               

        
        <?php
            }
           if($user_role == 7 || $user_role == 8){
            
        ?>
        <li class="nav-item has-submenu">
        <a class="nav-link" href="#">
            <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-buildings-fill" viewBox="0 0 16 16">
            <path d="M15 .5a.5.5 0 0 0-.724-.447l-8 4A.5.5 0 0 0 6 4.5v3.14L.342 9.526A.5.5 0 0 0 0 10v5.5a.5.5 0 0 0 .5.5h9a.5.5 0 0 0 .5-.5V14h1v1.5a.5.5 0 0 0 .5.5h3a.5.5 0 0 0 .5-.5zM2 11h1v1H2zm2 0h1v1H4zm-1 2v1H2v-1zm1 0h1v1H4zm9-10v1h-1V3zM8 5h1v1H8zm1 2v1H8V7zM8 9h1v1H8zm2 0h1v1h-1zm-1 2v1H8v-1zm1 0h1v1h-1zm3-2v1h-1V9zm-1 2h1v1h-1zm-2-4h1v1h-1zm3 0v1h-1V7zm-2-2v1h-1V5zm1 0h1v1h-1z"/>
            </svg>
            RHE Data  
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
            <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
            </svg>
        </a>
        <ul class="submenu collapse">
            <li class=""><?= l('RHE Wise Flat List','rhe_wise_flat_list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            <li class=""><?= l('RHE Flat Master','update_flat',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            <li class=""><?= l('Add RHE Block','add_block',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
        </ul>
        </li>
        <li class="nav-item has-submenu">
        <a class="nav-link" href="#">
            <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" fill="currentColor" class="bi bi-person-vcard-fill" viewBox="0 0 16 16">
            <path d="M0 4a2 2 0 0 1 2-2h12a2 2 0 0 1 2 2v8a2 2 0 0 1-2 2H2a2 2 0 0 1-2-2zm9 1.5a.5.5 0 0 0 .5.5h4a.5.5 0 0 0 0-1h-4a.5.5 0 0 0-.5.5M9 8a.5.5 0 0 0 .5.5h4a.5.5 0 0 0 0-1h-4A.5.5 0 0 0 9 8m1 2.5a.5.5 0 0 0 .5.5h3a.5.5 0 0 0 0-1h-3a.5.5 0 0 0-.5.5m-1 2C9 10.567 7.21 9 5 9c-2.086 0-3.8 1.398-3.984 3.181A1 1 0 0 0 2 13h6.96q.04-.245.04-.5M7 6a2 2 0 1 0-4 0 2 2 0 0 0 4 0"/>
            </svg>
            Occupant Data  
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-chevron-down float-end mt-1" viewBox="0 0 16 16">
            <path fill-rule="evenodd" d="M1.646 4.646a.5.5 0 0 1 .708 0L8 10.293l5.646-5.647a.5.5 0 0 1 .708.708l-6 6a.5.5 0 0 1-.708 0l-6-6a.5.5 0 0 1 0-.708" />
            </svg>
        </a>
        <ul class="submenu collapse">
            <?php if($user_role == 7){?>
                <li class=""><?= l('Occupant Data Entry','rhewise_flatlist',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
            <?php }else if($user_role == 8){?>
                <li class=""><?= l('Occupant Data Approve','rhewise_occupantlist',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li> 
            <?php }
            ?>
            <li class=""><?= l('Occupant List','view-occupant-list',array('html'=>true, 'attributes'=>array('class'=>array('nav-link')))); ?></li>
        </ul>
        </li>

        <?php
            }
            //sd end 20-06-2024
        ?>

        <!-- <li class="nav-item">
            <?= l('Allotment','#',array('html' =>true, 'attributes' => array('class' => array('nav-link')))); ?>
        </li>  -->

        <li class="nav-item">
            <?= l('<i class="fa fa-sign-out" aria-hidden="true"></i> Logout','/user/logout',array('html' =>true, 'attributes' => array('class' => array('nav-link')))); ?>
        </li>        
    </ul>
    <img src="<?= $base_root.$base_path ?>sites/all/themes/housingtheme/images/designed-by-nic.png" class="w-100">
</div>