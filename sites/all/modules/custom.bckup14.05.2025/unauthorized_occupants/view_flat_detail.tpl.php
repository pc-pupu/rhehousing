<?php
	$isVal = $output[0];
	if($isVal){
		$data = $output[1];
	}
?>

<div class="table-bottom">
	
	<?php
    echo l('<img height="18" width="18" src="../'.drupal_get_path('module', 'unauthorized_occupants').'/images/pdf_icon.png" title="Download Occupied Flat Details" alt="PDF Icon">Download Occupied Flat Details', 'occupied_flat_details_pdf/'.encrypt_url($data->flat_id).'/occupied_flat_details_'.time(), array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px')));
    ?>
           
</div>

<div class="table-bottom">
	<table>
        <tr>
  			<th colspan="2" style="background: none repeat scroll 0 0 #F8F8F8;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family: 'Dosis',Arial,Verdana,serif;" class="first">Occupied Flat Information</th>
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
      		<th >Block</th>
      		<td ><?php echo $data->block_name;?></td>
    	</tr>
        <tr>
      		<th >Flat No.</th>
      		<td ><?php echo $data->flat_no;?></td>
    	</tr>
    </table>
</div>