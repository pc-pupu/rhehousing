<?php
	$isVal = $output[0];
	if($isVal){
		$data = $output[1];
	}

?>

<div class="table-bottom">
	<table>
        <tr>
  			<th colspan="2" style="background: none repeat scroll 0 0 #F8F8F8;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Allotment Information</th>
  		</tr>
        <tr>
      		<th >Allottee Name</th>
      		<td ><?php echo $data->applicant_name;?></td>
    	</tr>
        <tr>
      		<th >Allotment No.</th>
      		<td ><?php echo $data->allotment_no;?></td>
    	</tr>
        <tr>
      		<th >Allotment Date</th>
      		<td ><?php echo implode('/', array_reverse(explode('-', $data->allotment_date)));?></td>
    	</tr>
        <tr>
      		<th >Flat Type</th>
      		<td ><?php echo $data->flat_type;?></td>
    	</tr>
        <tr>
      		<th >District Name</th>
      		<td ><?php echo $data->district_name;?></td>
    	</tr>
        <tr>
      		<th >Estate Name</th>
      		<td ><?php echo $data->estate_name;?></td>
    	</tr>
        <tr>
      		<th >Estate Address</th>
      		<td ><?php echo $data->estate_address;?></td>
    	</tr>
        <tr>
      		<th >Flat No.</th>
      		<td ><?php echo $data->flat_no;?></td>
    	</tr>
    </table>
</div>