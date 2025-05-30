<?php
/*all housing list*/
function all_housing_list($flat_type_id = 0, $flat_category_id = 0) {
	
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he',
		'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd',
		'he.district_code = hd.district_code');
	$query->addField('hf', 'estate_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id', $flat_type_id, '=');
	$db_and->condition('hf.flat_category_id', $flat_category_id, '=');
	$query->condition($db_and);
	
	$query->groupBy('hf.estate_id');
	$query->groupBy('he.estate_name');
	$query->groupBy('he.estate_address');
	$query->groupBy('hd.district_name');
	
	$query->orderBy('district_name', 'ASC');
	$query->orderBy('estate_id', 'ASC');
	
	//$query->extend('TableSort')->extend('PagerDefault')->limit(1);
	//echo $query;
	return $query->execute();
}	

/*rhe flat vacancy list*/
function rhe_flat_allotment_list($flat_type_id = 0, $status_id = 0, $flat_category_id = 0) {
	
	$query = db_select('housing_flat', 'hf');
	$query->innerJoin('housing_estate', 'he',
		'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd',
		'he.district_code = hd.district_code');
	$query->innerJoin('housing_flat_type', 'hft',
		'hft.flat_type_id = hf.flat_type_id');
	$query->addField('hf', 'estate_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	$query->addField('hft', 'flat_type');
	
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id',$flat_type_id,'=');
	$db_and->condition('hf.flat_status_id',$status_id,'=');
	$db_and->condition('hf.flat_category_id',$flat_category_id,'=');
	$query->condition($db_and);
	
	$query->groupBy('hf.estate_id');
	$query->groupBy('he.estate_name');
	$query->groupBy('he.estate_address');
	$query->groupBy('hd.district_name');
	$query->groupBy('hft.flat_type');
	$query->orderBy('district_name', 'ASC');
	$query->orderBy('estate_id', 'ASC');
	//$query->extend('TableSort')->extend('PagerDefault')->limit(1);
	//echo $query;
	return $query->execute();
}	
function rhe_flat_allotment_list_rst_estate_list($flat_type_id = 0, $status_id = 0, $estate_id = 0, $flat_category_id = 0) {
	$query = db_select('housing_flat', 'hf');
	$query->addField('hf','flat_id');
	$query->addField('hf','flat_no');
	$db_and = db_and();
	$db_and->condition('hf.flat_type_id',$flat_type_id,'=');
	$db_and->condition('hf.flat_status_id',$status_id,'=');
	$db_and->condition('hf.estate_id',$estate_id,'=');
	$db_and->condition('hf.flat_category_id',$flat_category_id,'=');
	$query->condition($db_and);
	$query->orderBy('estate_id', 'ASC');
	$query->orderBy('flat_id', 'ASC');
	//echo $query;
	return $query->execute();
}
function rhe_flat_allotment_list_rst_estate($flat_type_id = 0, $status_id = 0, $estate_id = 0, $flat_category_id = 0) {

	$result = rhe_flat_allotment_list_rst_estate_list($flat_type_id, $status_id, $estate_id, $flat_category_id);
	$output = array();
	$output[] = $result->rowCount();
	$str = '';
	if($result->rowCount() > 0){
		$i = 0;
		while($data = $result->fetchObject()){
			if($i == 0){
				$str.=$data->flat_no;
				$i++;
			}else{
				$str.=', '.$data->flat_no;
			}
		}
	}

	
	$output[] = $str;
	return $output; 
}

function rhe_flat_status($flat_status_id=0) {
	$query=db_select('housing_flat_status','hfs');
	$query->addField('hfs','flat_status');
	$query->condition('hfs.flat_status_id',$flat_status_id,'=');
	
	return $query->execute();
}
