<?php 

//echo "<pre>";print_r($output['page_status']);die;
if(isset($output['page_status'])){
	$page_status=$output['page_status'];
}else{
	$page_status=null;
}
$url = decrypt_url($output['url']);//echo $url;
$status = $output['status'];
$options['attributes']['class'] = array('button','link-button','round','child-tab','child-color-blue');
$options['html'] = TRUE;
$options1['attributes']['class'] = array('button','link-button','round','child-tab','child-color-sea');
$options1['html'] = TRUE;
if($status == 'applied'){
	drupal_set_title('New Application List');
}
else if($status == 'ddo_verified_1'||$status == 'ddo_verified_2'||$status=='housing_sup_approved_1'||$status=='housing_official_approved'||$status=='housing_sup_approved_2'){
	drupal_set_title('Verified Application List');
}
else if($status == 'ddo_reject_1'||$status == 'ddo_reject_2'||$status=='housing_sup_reject_1'||$status=='housing_official_rejected'||$status=='housing_sup_reject_2'){
	drupal_set_title('Rejected Application List');
}
?>

<div class="breadcrumb_links" style="padding-left: 75px;"> 
<?php
$span_class = $url == 'new-apply' ? 'class="child-span-sea"' : 'class="child-span-blue"';
$str = $output['new-apply'] != 0 ? '<span '.$span_class.'>'.$output['new-apply'].'</span>' : '';
 echo l('New Allotment'.$str , 'view_application_list/'.encrypt_url($status).'/'.encrypt_url('new-apply').'/'.$page_status,$url == 'new-apply' ? $options : $options1);
 $span_class = $url == 'vs' ? 'class="child-span-sea"' : 'class="child-span-blue"';
$str = $output['vs'] != 0 ? '<span '.$span_class.'>'.$output['vs'].'</span>' : ''; 
  echo l('Floor Shifting'.$str , 'view_application_list/'.encrypt_url($status).'/'.encrypt_url('vs').'/'.$page_status,$url == 'vs' ?$options : $options1);
  $span_class = $url == 'cs' ? 'class="child-span-sea"' : 'class="child-span-blue"';
  $str = $output['cs'] != 0 ? '<span '.$span_class.'>'.$output['cs'].'</span>' : '';
   echo l('Category Shifting'.$str , 	'view_application_list/'.encrypt_url($status).'/'.encrypt_url('cs').'/'.$page_status,$url == 'cs' ?$options : $options1);

?>
</div>
<!--padding-left: 54px;-->
<div class="breadcrumb_links" style="padding-left: 50px;">
<?php
$span_class = $url == 'new_license'?'class="child-span-sea"':'class="child-span-blue"';
$str = $output['new_license'] != 0 ? '<span '.$span_class.'>'.$output['new_license'].'</span>': '';
 echo l('New Licence'.$str , 	'view_application_list/'.encrypt_url($status).'/'.encrypt_url('new_license'),$url == 'new_license'?$options:$options1);
 //new code
 	$span_class = $url == 'vs_licence'?'class="child-span-sea"':'class="child-span-blue"';
	$str = $output['vs_licence'] != 0 ? '<span '.$span_class.'>'.$output['vs_licence'].'</span>': '';
	 echo l('Floor Shifting Licence'.$str , 	'view_application_list/'.encrypt_url($status).'/'.encrypt_url('vs_licence'),$url == 
	 'vs_licence'?$options:$options1);
 
 	$span_class = $url == 'cs_licence'?'class="child-span-sea"':'class="child-span-blue"';
	$str = $output['cs_licence'] != 0 ? '<span '.$span_class.'>'.$output['cs_licence'].'</span>': '';
	 echo l('Category Shifting Licence'.$str , 	'view_application_list/'.encrypt_url($status).'/'.encrypt_url('cs_licence'),$url == 
	 'cs_licence'?$options:$options1);
 //end
 /*$span_class = $url == 'renew_license'?'class="child-span-sea"':'class="child-span-blue"';
 $str = $output['renew_license'] != 0 ? '<span '.$span_class.'>'.$output['renew_license'].'</span>': '';
	 echo l('Renew Licence'.$str , 	'view_application_list/'.encrypt_url($status).'/'.encrypt_url('renew_license'),$url == 'renew_license'?$options:$options1);*/
?>
  </div>
<div class="ideabox">
  <?php if($url == 'new-apply'){?>
  This application is for the Applicant users to apply for new allotment .He/ She can save draft application before final submission and then can finally submit application dully authenticated by concerned DDO’s to be sent to the housing department for further processing.
  <?php }?>
  <?php if($url == 'vs'){?>
  This application is for the existing Occupant users apply for allotment shifting in the same building , application dully authenticated by concerned DDO’s. He/ She can save application before final submission of application for future modification. .He/ She can save draft application before final submission and then can finally submit application dully authenticated by concerned DDO’s to be sent to the housing department for further processing.
  <?php }?>
  <?php if($url == 'cs'){?>
  This application is for the existing Occupant users for allotment shifting to upgrade housing type .  He/She can save draft application before final submission and then can finally submit application dully authenticated by concerned DDO’s to be sent to the housing department for further processing.
  <?php }?>
  <?php if($url == 'new_license'){?>
  This application is for the Applicant users to apply for new licence for occupation, application dully authenticated by concerned DDO’s.
  <?php }?>
  
  <!--new code-->
  	<?php if($url == 'vs_licence'){?>
  This application is for the Applicant users to apply for vs licence for occupation, application dully authenticated by concerned DDO’s.
  <?php }?>
  
  <?php if($url == 'cs_licence'){?>
  This application is for the Applicant users to apply for cs licence for occupation, application dully authenticated by concerned DDO’s.
  <?php }?>
  <!--end-->
  
  <?php if($url == 'renew_license'){?>
  This application is for the Applicant users to apply for renew his / her licence for occupation, application dully authenticated by concerned DDO’s.
  <?php }?>
  </br>
  <ul class="links inline">
    <li class="node-readmore">
      <?php 
	  //$str = '<span class="element-invisible">';
	  	$str = '<span>';
			if($url == 'new-apply'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for New Allotment';
			}
			if($url == 'vs'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for Floor Shifting';
			}
			if($url == 'cs'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for Category Shifting';
			}
			if($url == 'new_license'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for New Licence';
			}
		
		//new code
			if($url == 'vs_licence'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for Floor Shifting Licence';
			}
			if($url == 'cs_licence'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for Category Shifting Licence';
			}
		//
		
			if($url == 'renew_license'){
				$str.='<span id="go_to_app_page">';
				$str.='View All Application for Renew Licence';
			}
		
		$str.='</span>';
		
     	echo l($str, 'view_application/'.encrypt_url($status).'/'.encrypt_url($url).'/'.$page_status,
			  array('html' => TRUE,
				   'attributes'=>array(
				   'rel' => 'tag',
				   'title' => 'View All Application',
				  // 'target' => '_blank'
				   )
			   )
		);

     ?>
    
      </li>
  </ul>
  
</div>