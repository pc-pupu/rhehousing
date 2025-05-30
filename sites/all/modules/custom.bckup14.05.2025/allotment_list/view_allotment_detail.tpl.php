<?php
	$isVal = $output[0];
	if($isVal){
		$data = $output[1];
	}

?>

<div class="table-bottom">
	<table>
        <tr>
  			<th colspan="2" style="background: none repeat scroll 0 0 #5996d9;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Allotment Information</th>
  		</tr>
        <tr>
      		<th style="background-color: #415b92">Allottee Name</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->applicant_name;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Allotment No.</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->allotment_no;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Allotment Category</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->allotment_category;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Allotment Date</th>
      		<td style="background-color: #e1f5fb"><?php echo implode('/', array_reverse(explode('-', $data->allotment_date)));?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Flat Type</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->flat_type;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">District Name</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->district_name;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Estate Name</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->estate_name;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Estate Address</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->estate_address;?></td>
    	</tr>
        <tr>
      		<th style="background-color: #415b92">Flat No.</th>
      		<td style="background-color: #e1f5fb"><?php echo $data->flat_no;?></td>
    	</tr>
    </table>
</div>