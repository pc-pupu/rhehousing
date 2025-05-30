
<?php
global $user;
$output = decrypt_url($output);
$options['attributes']['class'] = array('button','link-button','round','child-tab','child-color-blue');
$options['html'] = TRUE;
$options1['attributes']['class'] = array('button','link-button','round','child-tab','child-color-sea');
$options1['html'] = TRUE;

$options2['attributes']['class'] = array('button','link-button','round','child-tab','child-color-green');
$options2['html'] = TRUE;
$options3['attributes']['class'] = array('button','link-button','round','child-tab','child-color-red');
$options3['html'] = TRUE;
$options4['attributes']['class'] = array('button','link-button','round','child-tab','child-color-yellow');
$options4['html'] = TRUE;

$result = online_application_status($user->uid);

if($result->rowCount() > 0) {
?>
<div class="breadcrumb_links" style="padding-left: 115px; font-size:16px">
<?php
//for new application
	$na_result = online_application_status($user->uid, 'NA');
	$na_data = $na_result->fetchObject();
	if($na_result->rowCount() > 0) {
		if($na_data->app_status == 'draft') {
			echo l('New Allotment' , 'online_application/'.encrypt_url('new-apply'), $output == 'new-apply'?$options:$options4);		
		} else if($na_data->app_status == 'reject') {
			echo l('New Allotment' , 'online_application/'.encrypt_url('new-apply'), $output == 'new-apply'?$options:$options3);
		} else {
			echo l('New Allotment' , 'online_application/'.encrypt_url('new-apply'), $output == 'new-apply'?$options:$options2);	
		}
			
	} else {
		echo l('New Allotment' , 'online_application/'.encrypt_url('new-apply'), $output == 'new-apply'?$options:$options1);		
	}
//end

//for vs
	$vs_result = online_application_status($user->uid, 'VS');
	$vs_data = $vs_result->fetchObject();
	if($vs_result->rowCount() > 0) {
		if($vs_data->app_status == 'draft') {
			echo l('Floor Shifting' , 'online_application/'.encrypt_url('vs'), $output == 'vs'?$options:$options4);
		} else if($na_data->app_status == 'reject') {
			echo l('Floor Shifting' , 'online_application/'.encrypt_url('vs'), $output == 'vs'?$options:$options3);
		}else {
			echo l('Floor Shifting' , 'online_application/'.encrypt_url('vs'), $output == 'vs'?$options:$options2);
		}
			
	} else {
		echo l('Floor Shifting' , 'online_application/'.encrypt_url('vs'), $output == 'vs'?$options:$options1);
	}
//end

//for cs
	$cs_result = online_application_status($user->uid, 'CS');
	$cs_data = $cs_result->fetchObject();
	if($cs_result->rowCount() > 0) {
		if($cs_data->app_status == 'draft') {
			echo l('Category Shifting' , 'online_application/'.encrypt_url('cs'), $output == 'cs'?$options:$options4);
		} else if($na_data->app_status == 'reject') {
			echo l('Category Shifting' , 'online_application/'.encrypt_url('cs'), $output == 'cs'?$options:$options3);
		}else {
			echo l('Category Shifting' , 'online_application/'.encrypt_url('cs'), $output == 'cs'?$options:$options2);
		}
			
	} else {
		echo l('Category Shifting' , 'online_application/'.encrypt_url('cs'), $output == 'cs'?$options:$options1);
	}
//end

?>
</div>
<!--padding-left: 42px;-->
<div class="breadcrumb_links" style="padding-left: 60px; font-size:16px">
<?php
//for new licence
	$nl_result = online_application_status($user->uid, 'NL');
	$nl_data = $nl_result->fetchObject();
	if($nl_result->rowCount() > 0) {
		if($nl_data->app_status == 'draft') {
			echo l('New Licence' , 'online_application/'.encrypt_url('new_license'), $output == 'new_license'?$options:$options4);
		} else if($na_data->app_status == 'reject') {
			echo l('New Licence' , 'online_application/'.encrypt_url('new_license'), $output == 'new_license'?$options:$options3);
		}else {
			echo l('New Licence' , 'online_application/'.encrypt_url('new_license'), $output == 'new_license'?$options:$options2);
		}
			
	} else {
		echo l('New Licence' , 'online_application/'.encrypt_url('new_license'), $output == 'new_license'?$options:$options1);
	}
//end

//for vs licence
	$vsl_result = online_application_status($user->uid, 'VSL');
	$vsl_data = $vsl_result->fetchObject();
	if($vsl_result->rowCount() > 0) {
		if($vsl_data->app_status == 'draft') {
			echo l('Floor Shifting Licence' , 'online_application/'.encrypt_url('vs_licence'), $output == 'vs_licence'?$options:$options4);
		} else if($na_data->app_status == 'reject') {
			echo l('Floor Shifting Licence' , 'online_application/'.encrypt_url('vs_licence'), $output == 'vs_licence'?$options:$options3);
		}else {
			echo l('Floor Shifting Licence' , 'online_application/'.encrypt_url('vs_licence'), $output == 'vs_licence'?$options:$options2);
		}
			
	} else {
		echo l('Floor Shifting Licence' , 'online_application/'.encrypt_url('vs_licence'), $output == 'vs_licence'?$options:$options1);
	}
//end

//for cs licence
	$csl_result = online_application_status($user->uid, 'CSL');
	$csl_data = $csl_result->fetchObject();
	if($csl_result->rowCount() > 0) {
		if($csl_data->app_status == 'draft') {
			echo l('Category Shifting Licence' , 'online_application/'.encrypt_url('cs_licence'), $output == 'cs_licence'?$options:$options4);
		} else if($na_data->app_status == 'reject') {
			echo l('Category Shifting Licence' , 'online_application/'.encrypt_url('cs_licence'), $output == 'cs_licence'?$options:$options3);
		}else {
			echo l('Category Shifting Licence' , 'online_application/'.encrypt_url('cs_licence'), $output == 'cs_licence'?$options:$options2);
		}
			
	} else {
		echo l('Category Shifting Licence' , 'online_application/'.encrypt_url('cs_licence'), $output == 'cs_licence'?$options:$options1);
	}
//end

?>
</div>
<?php
} else {
?>
<div class="breadcrumb_links" style="padding-left: 110px; font-size:16px">
	Invalid Access.
</div>
<?php
}
?>

<div class="ideabox">
<?php if($output == 'new-apply'){?>
This application is for the Applicant users to apply for new allotment .He/ She can save draft application before final submission and then can finally submit application dully authenticated by concerned DDO’s to be sent to the housing department for further processing.
<?php }?>
<?php if($output == 'vs'){?>
This application is for the existing Occupant users apply for allotment shifting in the same building , application dully authenticated by concerned DDO’s. He/ She can save application before final submission of application for future modification. .He/ She can save draft application before final submission and then can finally submit application dully authenticated by concerned DDO’s to be sent to the housing department for further processing.
<?php }?>
<?php if($output == 'cs'){?>
This application is for the existing Occupant users for allotment shifting to upgrade housing type .  He/She can save draft application before final submission and then can finally submit application dully authenticated by concerned DDO’s to be sent to the housing department for further processing.
<?php }?>
<?php if($output == 'new_license'){?>
This application is for the Applicant users to apply for licence for occupation after new allotment, application dully authenticated by concerned DDO’s. 
<?php }?>

<!--new code-->
<?php if($output == 'vs_licence'){?>
This application is for the Applicant users to apply for licence for occupation after vs allotment, application dully authenticated by concerned DDO’s. 
<?php }?>
<?php if($output == 'cs_licence'){?>
This application is for the Applicant users to apply for licence for occupation after cs allotment, application dully authenticated by concerned DDO’s. 
<?php }?>
<!--end-->

<?php if($output == 'renew_license'){?>
This application is for the existing Occupant users to apply for Licence renewal after period of licence for staying in the flat are expired. The application dully authenticated by concerned DDO’s. 
<?php }?>
</br>
<ul class="links inline">
	<li class="node-readmore">

  <?php 
	//$str = '<span class="element-invisible">';
	$str = '<span>';
	  if($output == 'new-apply'){
		$str.='<span id="go_to_app_page">';
      	$str.='Go to Application page for New Allotment';
      }
      if($output == 'vs'){
		$str.='<span id="go_to_app_page">';
     	$str.='Go to Application page for Floor Shifting';
      }
      if($output == 'cs'){
		$str.='<span id="go_to_app_page">';
     	$str.='Go to Application page for Category Shifting';
      }
      if($output == 'new_license'){
		$str.='<span id="go_to_app_page">';
      	$str.='Go to Application page for New Licence';
      }
	  
	  //new code
	  if($output == 'vs_licence'){
		$str.='<span id="go_to_app_page">';
      	$str.='Go to Application page for Floor Shifting Licence';
      }
	  if($output == 'cs_licence'){
		$str.='<span id="go_to_app_page">';
      	$str.='Go to Application page for Category Shifting Licence';
      }
	  //end
	  
	  if($output == 'renew_license'){
		$str.='<span id="go_to_app_page">';
      	$str.='Go to Application page for Renew Licence';
      }
	
	$str.='</span>';

	echo l($str, $output, 
		array('html' => TRUE,
			'attributes'=>array(
				'rel' => 'tag',
				'title' => $str,
				'target' => '_blank',
			)
		)
	);

     ?>

	</li>
</ul>
</div>
<br />

<div><img width="15" height="15" src="<?php print base_path() . drupal_get_path('module', 'online_application') ;?>/images/blue_color_logo.png" alt="Currently Selected" /> - <strong>Currently Selected.</strong><br /></div>

<div><img width="15" height="15" src="<?php print base_path() . drupal_get_path('module', 'online_application') ;?>/images/sea_blue_color_logo.jpg" alt="Not Applied" /> - <strong>Not Applied.</strong><br /></div>

<div><img width="15" height="15" src="<?php print base_path() . drupal_get_path('module', 'online_application') ;?>/images/yellow_color_logo.jpg" alt="Save as Draft" /> - <strong>Save as Draft.</strong><br /></div>

<div><img width="15" height="15" src="<?php print base_path() . drupal_get_path('module', 'online_application') ;?>/images/green_color_logo.png" alt="Applied" /> - <strong>Applied.</strong><br /></div>

<div><img width="15" height="15" src="<?php print base_path() . drupal_get_path('module', 'online_application') ;?>/images/red_color_logo.png" alt="Reject" /> - <strong>Reject.</strong></div>