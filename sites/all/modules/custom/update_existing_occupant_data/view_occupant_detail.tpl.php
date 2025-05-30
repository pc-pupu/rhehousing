<?php

$isVal = $output[0];
if($isVal){
	$data = $output[1];
?>
<div class="table-bottom">
  <table>
    <tr>
      <th class="first">RHE Flat No</th>
      <th>RHE Name</th>
      <th>Flat Type</th>
      <th>Allotment No</th>
      <th>Allotment Date</th>
      <th>Licence No</th>
      <th>Licence Issue Date</th>
      <th>Licence Expiry Date</th>
    </tr>
    <tr>
      <td class="first"><?php echo $data->flat_no; ?></td>
      <td><?php echo $data->estate_name; ?></td>
      <td><?php echo $data->flat_type; ?></td>
      <td><?php echo $data->allotment_no; ?></td>
      <td><?php echo $data->allotment_date; ?></td>
      <td><?php echo $data->license_no; ?></td>
      <td><?php echo $data->license_issue_date ; ?></td>
      <td><?php echo $data->license_expiry_date; ?></td>
    </tr>
  </table>
</div>

<div class="table-bottom">
  <table >
    <tr>
      <th class="first">Applicant Name</th>
      <th>Father's / Husband Name</th>
      <th>Gender</th>
      <th>Date of Birth</th>
      <th>Mobile No</th>
      <th>Email ID</th>
    </tr>
    <tr>
      <td class="first"><?php echo $data->applicant_name;?></td>
      <td><?php echo $data->guardian_name;?></td>
      <td><?php echo $data->gender == 'M'?'Male':'Female';?></td>
      <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_birth)));?></td>
      <td><?php echo $data->mobile_no;?></td>
      <td><?php echo $data->mail;?></td>
    </tr>
  </table>
</div>

<div class="table table-bottom">
  <table >
    <tr>
      <th class="first">Applicatnt's Office Name</th>
      <th>Applicatnt's Office Street</th>
      <th>Applicatnt's Office City/ Town/ Village</th>
      <th>Applicatnt's Office Post Office</th>
      <th>Applicatnt's Office Pin Code</th>
      <th>DDO Designation</th>
      <th>DDO Address</th>
    </tr>
    <tr>
      <td class="first"><?php echo $data->office_name;?></td>
      <td><?php echo $data->office_street;?></td>
      <td><?php echo $data->office_city_town_village;?></td>
      <td><?php echo $data->office_post_office;?></td>
      <td><?php echo $data->office_pin_code;?></td>
      <td><?php echo $data->ddo_designation;?></td>
      <td><?php echo $data->ddo_address;?></td>
    </tr>
  </table>
</div>

<div class="table table-bottom">
  <table>
    <tr>
      <th class="first">Applicant's Designation</th>
      <th>Applicant's Headquarter</th>
      <th>Applicant's Posting Place</th>
      <th>Applicatnt's Pay Band</th>
      <th>Applicatnt's Pay in Pay Band</th>
      <th>Applicatnt's Grade Pay</th>
      <th>Applicatnt's Date of Joining</th>
      <th>Applicatnt's Date of Retirement</th>
    </tr>
    <tr>
      <td class="first"><?php echo $data->applicant_designation;?></td>
      <td><?php echo $data->applicant_headquarter;?></td>
      <td><?php echo $data->applicant_posting_place;?></td>
      <?php
            if($data->scale_from == 0 && $data->scale_to != 0) {
                $str =  $data->payband.' (Below Rs '.$data->scale_to.'/-)';
            }
			else if($data->scale_from != 0 && $data->scale_to == 0) {
                $str =  $data->payband.' (Rs '.$data->scale_from.'/- and above)';
            }
			else{
                $str = $data->payband.' (Rs '.$data->scale_from.'/- to Rs '.$data->scale_to.'/-)';
            }
	  ?>
      <td><?php echo $str;?></td>
      <td><?php echo $data->pay_in_the_pay_band;?></td>
      <td><?php echo $data->grade_pay;?></td>
      <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_joining)));?></td>
      <td><?php echo implode('/', array_reverse(explode('-', $data->date_of_retirement)));?></td>
    </tr>
  </table>
</div>


<?php 
}
else { ?>

	Invalid Access

<?php 
} 
?>