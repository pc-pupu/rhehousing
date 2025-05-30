/*jQuery(document).ready(function(){
		jQuery("#al_date").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		changeMonth: true,
		changeYear: true,
		yearRange: "-50:+0",
		autoSize: true
	});	
});

jQuery(document).ready(function(){
		jQuery("#li_date").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		changeMonth: true,
		changeYear: true,
		yearRange: "-50:+0",
		autoSize: true
	});	
});*/



	function validate_renew_licence_form(){
		//alert('OK'); 
		//return false;
		var formElements1 = validate_common_application_form();
		formElements2 =
		{
			"rhe_name":["RHE Name","streetAddress"],
			"block_no":["Block No","alphaNumeric"],
			"flat_no":["Flat No","flatNo"],
			"allotment_no":["Allotment No","no"],
			"allotment_date":["Allotment Date","date"],
			"license_no":["Licence No","no"],
			"license_date":["Licence Date","date"]
		};	
		var formElements = jQuery.extend(formElements1, formElements2);
		
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}		
	}