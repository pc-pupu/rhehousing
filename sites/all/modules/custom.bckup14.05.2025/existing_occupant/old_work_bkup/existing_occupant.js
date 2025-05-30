	/*function validate_computer_serial_no_search_form(){
		var formElements =
		{
			"computer_serial_no":["Computer Serial No", "alphaNumeric"]
		};
			
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
		
	}*/




	jQuery(document).ready(function(){
			jQuery("#edit-dob").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-70:-18",
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
			autoSize: true
		});	
	});
	
	
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
	
	
	jQuery(document).ready(function() {
		
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
		
	});
	
	
	function validate_existing_occupant_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"occupied_district":["District Name","onlyAlphabet"],
			"occupied_estate":["Rental Housing Estate Name","housingAddress"],
			"occupied_block":["Block Name","frontSlash"],
			"occupied_flat":["Flat No.","flatNo"],
			
			"occupant_name":["Occupant Name","onlyAlphabet"],
			"occupant_father_name":["Father / Husband Name","onlyAlphabet"],
			
			"mobile":["Mobile No", "mobileNo"],
			"email":["Email Id", "emailAddress"],
			
			"dob":["Date of Birth","date"],
			"gender":["Gender", "radioBox"],
			"occupant_designation":["Designation", "onlyAlphabet"],
			"pay_band":["Pay Band", "selectBox"],
			"pay_in":["Pay in the Pay Band", "onlyNo"],
			
			"grade_pay":["Grade Pay", "onlyNo"],
			"gpf_no":["GPF No", "gpfNo"],
			
			"occupant_posting_place":["Place of Posting", "onlyAlphabet"],
			
			"occupant_headquarter":["Headquarter", "onlyAlphabet"],
			"doj":["Date of Joining", "date"],
			
			"dor":["Date of Retirement", "date"],
			
			"office_name":["Name of the Office", "hyphenFullStopAmpersand"],
			"office_street":["Street Name of the Office", "streetAddress"],
			"office_city":["City/Town/Village of the Office", "onlyAlphabet"],
			
			"office_post_office":["Post Office Name of the Office", "hyphenFullStop"],
			
			"office_pincode":["Pincode of the Office", "onlyNo"],
			
			"district":["DDO District", "selectBox"],
			"designation":["DDO Designation", "selectBox"],
			
			"rhe_flat_type":["Flat TYPE","flatType"],
			//"reason":["Allotment Category", "selectBox"],
			
		};
		
		
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