	<?php
	
		$isVal = $output[0];
		if($isVal){
			$online_app_id = $output[1];
			//die($online_app_id);
		$result = fetch_occupant_details($online_app_id);
			while($data = $result->fetchObject()) {	

        // echo "<pre>";print_r($data);die;
	?>
	
  <div class="">
      <!-- <table> -->
          <tr>
              <td>
                  <?php					
                  //  echo l('<img height="18" width="18" src="../'.drupal_get_path('module', 'existing_occupant').'/images/pdf_icon.png" title="Download Occupant Details" alt="PDF Icon">Download Occupant Details', 'occupant_detail_pdf/'.encrypt_url($online_app_id).'/Occupant_Details_'.$online_app_id, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px')));
                  echo l(' Download Occupant Details','occupant_detail_pdf/'.encrypt_url($online_app_id).'/Occupant_Details_'.$online_app_id,array('html'=>TRUE,'attributes' => array('target' => '_blank','class' => 'btn bg-success px-4 fa fa-download rounded-pill btn-sm text-white fw-bolder mb-2')));//sd 21-06-2024
                  ?>
              </td>
          </tr>
      <!-- </table> -->
  </div>
        
  <div class="table-bottom">
  <table class="table table-list">
    <tr>
        <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white; text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant Personal Information</th>
    </tr>
      <tr>
        <th style="background-color:#00000000" width="50%">Occupant Name</th>
        <td width="50%"><?php echo $data->applicant_name;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Father's / Husband Name</th>
        <td><?php echo $data->guardian_name;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Gender</th>
        <td><?php echo $data->gender == 'M'?'Male':'Female';?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Date of Birth</th>
        <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_birth)));?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Mobile No</th>
        <td><?php echo $data->mobile_no;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Email ID</th>
        <td><?php echo $data->mail ;?></td>
      </tr>
  <tr>
    <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant Official Information</th>
    </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Designation</th>
        <td ><?php echo $data->applicant_designation;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Office Headquarter</th>
        <td><?php echo $data->applicant_headquarter;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Place of Posting</th>
        <td><?php echo $data->applicant_posting_place;?></td>
      </tr>
      <tr>
      <th style="background-color:#00000000"> Occupant's Pay Band</th>
       <?php
             if($data->scale_from == 0 && $data->scale_to != 0){
                //$str =  $common_data->payband.' (Below Rs '.$common_data->scale_to.'/-)';
                $str =  $data->flat_type.' (Below Rs '.$data->scale_to.'/-)';
            }else if($data->scale_from != 0 && $data->scale_to == 0){
                //$str =  $common_data->payband.' (Rs '.$common_data->scale_from.'/- and above)';
                $str =  $data->flat_type.' (Rs '.$data->scale_from.'/- and above)';
            }else{
              //$str = $common_data->payband.' (Rs '.$common_data->scale_from.'/- to Rs '.$common_data->scale_to.'/-)';
              $str = $data->flat_type.' (Rs '.$data->scale_from.'/- to Rs '.$data->scale_to.'/-)';
            }?>
      <td><?php echo $str;?></td>
    </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Basic Pay</th>
        <td><?php echo $data->pay_in_the_pay_band;?></td>
      </tr>
      <!-- <tr>
        <th style="background-color:#00000000">Occupant's Grade Pay</th>
        <td><?php //echo $data->grade_pay;?></td>
      </tr> -->
      <!-- <tr>
        <th style="background-color:#00000000">Occupant's GPF No.</th>
        <td><?php //echo $data->gpf_no;?></td>
      </tr> -->
      <tr>
        <th style="background-color:#00000000">Occupant's Date of Joining</th>
        <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_joining)));?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Date of Retirement</th>
        <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_retirement)));?></td>
      </tr>
    <tr>
    <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant Office Address</th>
    </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Office Name</th>
        <td><?php echo $data->office_name;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Office Address</th>
        <td><?php echo $data->office_street;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Office City/ Town/ Village</th>
        <td><?php echo $data->office_city_town_village;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Office Post Office</th>
        <td><?php echo $data->office_post_office;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">Occupant's Office Pin Code</th>
        <td><?php echo $data->office_pin_code;?></td>
      </tr>
      <tr>
    <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant DDO Information</th>
    </tr>
      <tr>
        <th style="background-color:#00000000">DDO District</th>
        <td><?php echo $data->district_name;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">DDO Designation</th>
        <td><?php echo $data->ddo_designation;?></td>
      </tr>
      <tr>
        <th style="background-color:#00000000">DDO Address</th>
        <td><?php echo $data->ddo_address;?></td>
      </tr>
    </table>
  </div>
        
<?php
}
} else { ?>
	Invalid Access
<?php } ?>
