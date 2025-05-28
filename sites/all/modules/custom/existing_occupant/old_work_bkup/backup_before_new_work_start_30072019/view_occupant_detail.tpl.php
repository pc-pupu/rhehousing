	<?php
	
		$isVal = $output[0];
		if($isVal){
			$online_app_id = $output[1];
			//die($online_app_id);
		$result = fetch_occupant_details($online_app_id);
			while($data = $result->fetchObject()) {	
	?>
	
            <div class="table-bottom">
                <table>
                    <tr>
                        <td>
            <?php					
                echo l('<img height="18" width="18" src="../'.drupal_get_path('module', 'existing_occupant').'/images/pdf_icon.png" title="Download Occupant Details" alt="PDF Icon">Download Occupant Details', 'occupant_detail_pdf/'.encrypt_url($online_app_id).'/Occupant_Details_'.$online_app_id, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px')));
            ?>
                        </td>
                    </tr>
                </table>
            </div>
        
        <div class="table-bottom">
          <table >
        	<tr>
          		<th colspan="2" style="background: none repeat scroll 0 0 #5996d9; text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant Personal Information</th>
         	</tr>
            <tr>
              <th style="background-color:#a1baef" width="50%">Occupant Name</th>
              <td width="50%"><?php echo $data->applicant_name;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Father's / Husband Name</th>
              <td><?php echo $data->guardian_name;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Gender</th>
              <td><?php echo $data->gender == 'M'?'Male':'Female';?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Date of Birth</th>
              <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_birth)));?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Mobile No</th>
              <td><?php echo $data->mobile_no;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Email ID</th>
              <td><?php echo $data->mail ;?></td>
            </tr>
        <tr>
          <th colspan="2" style="background: none repeat scroll 0 0 #5996d9;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant Official Information</th>
          </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Designation</th>
              <td ><?php echo $data->applicant_designation;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Office Headquarter</th>
              <td><?php echo $data->applicant_headquarter;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Place of Posting</th>
              <td><?php echo $data->applicant_posting_place;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Pay Band</th>
              <?php
                     if($data->scale_from == 0 && $data->scale_to != 0){
                        $str =  $data->payband.' (Below Rs '.$data->scale_to.'/-)';
                    }else if($data->scale_from != 0 && $data->scale_to == 0){
                        $str =  $data->payband.' (Rs '.$data->scale_from.'/- and above)';
                    }else{
                        $str = $data->payband.' (Rs '.$data->scale_from.'/- to Rs '.$data->scale_to.'/-)';
                    }?>
              <td><?php echo $str;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Pay in Pay Band</th>
              <td><?php echo $data->pay_in_the_pay_band;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Grade Pay</th>
              <td><?php echo $data->grade_pay;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's GPF No.</th>
              <td><?php echo $data->gpf_no;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Date of Joining</th>
              <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_joining)));?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Date of Retirement</th>
              <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_retirement)));?></td>
            </tr>
          <tr>
          <th colspan="2" style="background: none repeat scroll 0 0 #5996d9;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant Office Address</th>
          </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Office Name</th>
              <td><?php echo $data->office_name;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Office Address</th>
              <td><?php echo $data->office_street;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Office City/ Town/ Village</th>
              <td><?php echo $data->office_city_town_village;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Office Post Office</th>
              <td><?php echo $data->office_post_office;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">Occupant's Office Pin Code</th>
              <td><?php echo $data->office_pin_code;?></td>
            </tr>
            <tr>
          <th colspan="2" style="background: none repeat scroll 0 0 #5996d9;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupant DDO Information</th>
          </tr>
            <tr>
              <th style="background-color:#a1baef">DDO District</th>
              <td><?php echo $data->district_name;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">DDO Designation</th>
              <td><?php echo $data->ddo_designation;?></td>
            </tr>
            <tr>
              <th style="background-color:#a1baef">DDO Address</th>
              <td><?php echo $data->ddo_address;?></td>
            </tr>
          </table>
        </div>
        
        <?php
			}
	} else { ?>
		Invalid Access
	<?php } ?>
