/*jQuery(document).ready(function(){
	//alert('ok');
	
	 
	  
	  jQuery('#chk_extra_doc').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-extra-doc').show();
        //alert('checked');
      
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-extra-doc').hide();
			//alert('not checked');
     
        }
    });
	  
	  
});


jQuery(document).ready(function(){
	
	
	
        if (jQuery('#chk_extra_doc').is(':checked')) {
			jQuery('.form-item-extra-doc').show();
        //alert('checked');
      
        } else {
			jQuery('.form-item-extra-doc').hide();
			//alert('not checked');
     
        }
    
	  
	  
});*/
jQuery(window).load(function () {
	jQuery('#overlay').fadeOut();
});

jQuery(document).ready(function () {
	var allotment_category = jQuery('#check_allotment_reason').val();
	//alert(allotment_category);
	if ((allotment_category != 'Transfer') && (allotment_category != 'Physically Handicaped Or Serious Illness') && (allotment_category != 'Officer on Transfer having earmarked Bungalow or Quater in their immediate previous posting')) {
		jQuery('.form-item-extra-doc').hide();
	}
	//alert('ok');
	//jQuery('[name=reason]').change(function(){
	jQuery('#check_allotment_reason').change(function () {
		//alert('ok');
		var allotment_category = jQuery(this).val();
		//alert(allotment_category);
		if (allotment_category == 'Transfer') {
			jQuery('.form-item-extra-doc').show();
		} else if (allotment_category == 'Physically Handicaped or Serious Illness') {    //debaleena 30-07-2024
			jQuery('.form-item-extra-doc').show();
		} else if (allotment_category == 'Recommended') {									//debaleena 30-07-2024
			jQuery('.form-item-extra-doc').show();
		}else if (allotment_category == 'Single Earning Lady') {					//debaleena 30-07-2024
			jQuery('.form-item-extra-doc').show();
		}else if (allotment_category == 'Legal Heir') {					//debaleena 30-07-2024
			jQuery('.form-item-extra-doc').show();
		}else {
			jQuery('.form-item-extra-doc').hide();
		}
	});
});

jQuery(document).ajaxSuccess(function () {
	var allotment_category = jQuery('#check_allotment_reason').val();
	if ((allotment_category != 'Transfer') && (allotment_category != 'Physically Handicaped Or Serious Illness') && (allotment_category != 'Officer on Transfer having earmarked Bungalow or Quater in their immediate previous posting')) {
		jQuery('.form-item-extra-doc').hide();
	}
	//alert('ok');
	//jQuery('[name=reason]').change(function(){
	jQuery('#check_allotment_reason').change(function () {
		//alert('ok');
		var allotment_category = jQuery(this).val();
		if (allotment_category == 'Transfer') {
			jQuery('.form-item-extra-doc').show();
		} else if (allotment_category == 'Physically Handicaped Or Serious Illness') {
			jQuery('.form-item-extra-doc').show();
		} else if (allotment_category == 'Officer on Transfer having earmarked Bungalow or Quater in their immediate previous posting') {
			jQuery('.form-item-extra-doc').show();
		} else {
			jQuery('.form-item-extra-doc').hide();
		}
	});


});




function validate_new_application_form() {
	//alert('OK'); 
	//return false;
	var formElements;
	var formElements1 = validate_common_application_form();
	var formElements2 =
	{
		"rhe_flat_type": ["Flat TYPE", "flatType"],
		"reason": ["Allotment Category", "selectBox"],

		"files[file]": ["Upload Your Latest Payslip", "fileUpload"],
		"files[scaned_sign]": ["Upload Your Scanned Signature", "fileUpload"],

	};

	//debolina start
	var formElements4 =
	{
		"first_preference": ["First Preference", "selectBox"],
		"second_preference": ["Second Preference", "selectBox"],
		"third_preference": ["Third Preference", "selectBox"],

	};
	//debolina end

	formElements = jQuery.extend(formElements1, formElements2,formElements4);////debolina start formElements4 added

	var allotment_category = jQuery('#check_allotment_reason').val();
	if (allotment_category == 'Transfer' || allotment_category == 'Physically Handicaped Or Serious Illness' || allotment_category == 'Officer on Transfer having earmarked Bungalow or Quater in their immediate previous posting') {
		var formElements3 =
		{
			"files[extra_doc]": ["Upload Allotment Category Supporting Document", "fileUpload"]
		}
		formElements = jQuery.extend(formElements, formElements3);
	}

	if (!validateForm(formElements)) {
		return false;
	} else {
		return true;
	}
}


