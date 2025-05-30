<?php
  function fetch_allotment_letter_list($flat_type_id = 0) {
	$flat_type = fetch_rhe_flat_name_rst_id($flat_type_id);
	$query = db_select('housing_allotment_letter', 'hal');
	$query->innerJoin('housing_flat', 'hf',
		'hal.flat_id = hf.flat_id');
	$query->innerJoin('housing_estate', 'he',
		'he.estate_id = hf.estate_id');
	$query->innerJoin('housing_online_application', 'hoa',
		'hal.online_application_id = hoa.online_application_id');
	$query->innerJoin('housing_applicant_official_detail', 'haod',
		'haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
	$query->innerJoin('housing_applicant', 'ha',
		'haod.uid = ha.uid');
	$query->leftJoin('housing_new_allotment_application', 'hna',
		'hna.online_application_id = hoa.online_application_id');
	$query->leftJoin('housing_vs_application', 'hva',
		'hva.online_application_id = hoa.online_application_id');
	$query->leftJoin('housing_cs_application', 'hca',
		'hca.online_application_id = hoa.online_application_id');
	$query->addField('hal', 'online_application_id');
	$query->addField('ha', 'applicant_name');
	$query->addField('hna', 'allotment_category','n_allotment_category');
	$query->addField('hva', 'allotment_category','v_allotment_category');
	$query->addField('hca', 'allotment_category','c_allotment_category');
	$query->addField('hf', 'flat_no');
	$query->addField('he', 'estate_name');
	$query->addField('hal', 'roaster_counter');
	$query->addField('hal', 'list_no');
	$query->condition('hal.flat_type',$flat_type,'=');
	$query->orderBy('hal.list_no','ASC');
	$query->orderBy('hal.roaster_counter','ASC');
	return $query->execute();
}
?>