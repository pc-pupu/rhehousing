	/*jQuery(document).ready(function(){
			jQuery("#edit-dob").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-70:-18",
			maxDate: "-18Y",
			autoSize: true
		});	
	});
	
	jQuery(document).ready(function(){
			jQuery("#edit-doj").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-70:+0",
			maxDate: "0",
			autoSize: true
		});	
	});
	
	jQuery(document).ready(function(){
			jQuery("#edit-dor").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-0:+70",
			minDate: "0",
			autoSize: true
		});	
	});*/
	
	
	/*jQuery(document).ready(function(){
			jQuery("#edit-doa").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-70:+0",
			autoSize: true
		});	
	});
	
	jQuery(document).ready(function(){
			jQuery("#allotment-date").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-70:+0",
			maxDate: "+0Y",
			autoSize: true
		});	
	});*/
	
	
	/*jQuery(document).ready(function() {
		
		jQuery("#mobile_no").keypress(function (e)  
		{ 
		  if( e.which!=8 && e.which!=0 && (e.which<48 || e.which>57))
		  {
			return false;
		  }	
		});
		
		
		jQuery(".numeric_positive").keypress(function (e)  
		{ 
		  if( e.which!=8 && e.which!=0 && (e.which<48 || e.which>57))
		  {
			return false;
		  }	
		});
		
	});*/
	
	function validate_rhewise_occupant_entry_form(){
		var formElements =
		{
			"rhe_name":["Rental Housing Estate Name","selectBox"],
			"flat_type":["Flat Type","selectBox"],
			"block_name":["Block Name","selectBox"],
			"flat_no":["Flat No.","selectBox"],
			//"hrms_id":["Employee HRMS ID", "hrmsId"],
		};
	//	console.log(formElements);	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
		
	}
	
	function validate_existing_occupant_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"occupied_district":["District Name","alphabetFullstop"],
			"occupied_estate":["Rental Housing Estate Name","alphabetFullstop"],
			"occupied_flattype":["Flat Type","flatType"],
			"occupied_block":["Block Name","frontSlash"],
			"occupied_flat":["Flat No.","flatNo"],
			
			"occupant_name":["Occupant Name","onlyAlphabet"],
			"occupant_father_name":["Father / Husband Name","onlyAlphabet"],
			
			"permanent_street":["Permanent Address", "streetAddress"],
			"permanent_city_town_village":["City / Town / Village", "onlyAlphabet"],
			"permanent_post_office":["Post Office", "hyphenFullStop"],
			"permanent_district":["District", "selectBox"],
			"permanent_pincode":["Pincode", "onlyNo"],
		}
		
		//if(jQuery("#chk_present_address").not(':checked')) {
		if(jQuery("#edit-chk-permanent-address-1").not(':checked')) {
			var formElements1 = 
			{
				"present_street":["Present Address", "streetAddress"],
				"present_city_town_village":["City / Town / Village", "onlyAlphabet"],
				"present_post_office":["Post Office", "hyphenFullStop"],
				"present_district":["District", "selectBox"],
				"present_pincode":["Pincode", "onlyNo"],
			}
			formElements = jQuery.extend(formElements, formElements1);
		}
		
		var formElements2 =
		{
			"mobile":["Mobile No", "mobileNo"],
			"email":["Email Id", "emailAddress"],
			"dob":["Date of Birth","date"],
			"gender":["Gender", "radioBox"],
			
			"hrmsid":["Employee HRMS ID", "hrmsId"],
			"occupant_designation":["Designation", "textArea"],
			"pay_band":["Pay Band", "selectBox"],
			//"pay_in":["Pay in the Pay Band", "onlyNo"],
			//"grade_pay":["Grade Pay", "onlyNo"],
			//"gpf_no":["GPF No", "gpfNo"],
			"occupant_posting_place":["Place of Posting", "onlyAlphabet"],
			"occupant_headquarter":["Headquarter", "onlyAlphabet"],
			"doj":["Date of Joining", "date"],
			"dor":["Date of Retirement", "date"],
			
			"office_name":["Name of the Office", "textArea"],
			"office_street":["Street Name of the Office", "streetAddress"],
			"office_city":["City/Town/Village of the Office", "onlyAlphabet"],
			"office_post_office":["Post Office Name of the Office", "hyphenFullStop"],
			"office_district":["District", "selectBox"],
			"office_pincode":["Pincode of the Office", "onlyNo"],
			"office_phone_no":["Telephone No.", "telephoneNo"],
			
			"district":["DDO District", "selectBox"],
			"designation":["DDO Designation", "selectBox"],
			
			"dol":["Date of License","date"]  , ///debaleena 28-08-2024
			//"rhe_flat_type":["Flat TYPE","flatType"],
			//"reason":["Allotment Category", "selectBox"],
			
		};
		
		formElements = jQuery.extend(formElements, formElements2);
		//return formElements;	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	
	
	/*function validate_all_ready_existing_occupant_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"allotment_no":["Allotment No.","no"],
			"allotment_date":["Allotment Date","date"],
			"occupied_estate":["Housing","selectBox"],
			"occupied_block":["Block","selectBox"],
			"occupied_flat":["Flat No.","selectBox"],
			
		};
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}		
	}*/