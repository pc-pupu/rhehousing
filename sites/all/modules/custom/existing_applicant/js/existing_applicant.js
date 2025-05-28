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
	
	
	jQuery(document).ready(function(){
			jQuery("#edit-doa").datepicker({
			dateFormat: "dd/mm/yy",
			//minDate: minDoj,
			changeMonth: true,
			changeYear: true,
			yearRange: "-70:+0",
			autoSize: true
		});	
	});


	jQuery("#edit-confirm-computer-serial-no").change(function(){
		alert("The text has been changed.");
	  });
	
	
	
	/*function isNumberKey(evt) {
		var charCode = (evt.which) ? evt.which : event.keyCode;
		if (charCode != 46 && charCode > 31
		&& (charCode < 48 || charCode > 57))
			return false;
	
		return true;
	}*/
	
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

	
	

	function validate_existing_applicant_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"applicant_name":["Applicant Name","alphabetFullstop"],
			"applicant_father_name":["Father / Husband Name","alphabetFullstop"],
			
			"permanent_street":["Permanent Address", "streetAddressEA"],
			"permanent_city_town_village":["City / Town / Village", "onlyAlphabetEA"],
			"permanent_post_office":["Post Office", "hyphenFullStopEA"],
			//"permanent_district":["District", "selectBox"],
			"permanent_pincode":["Pincode", "onlyNoEA"],
		}
		
		//if(jQuery("#chk_present_address").not(':checked')) {
		if(jQuery("#edit-chk-permanent-address-1").not(':checked')) {
			var formElements1 = 
			{
				"present_street":["Present Address", "streetAddressEA"],
				"present_city_town_village":["City / Town / Village", "onlyAlphabetEA"],
				"present_post_office":["Post Office", "hyphenFullStopEA"],
				//"present_district":["District", "selectBox"],
				"present_pincode":["Pincode", "onlyNoEA"],
			}
			formElements = jQuery.extend(formElements, formElements1);
		}
		
		var formElements2 =
		{
			"mobile":["Mobile No", "mobileNoEA"],
			"email":["Email Id", "emailAddressEA"],
			
			"dob":["Date of Birth","date"],
			"gender":["Gender", "radioBox"],
			
			"hrmsid":["Employee HRMS ID", "hrmsIdEA"],
			"app_designation":["Designation", "textArea"],
			"pay_band":["Pay Band", "selectBox"],
			"pay_in":["Pay in the Pay Band", "onlyNo"],
			
			"grade_pay":["Grade Pay", "onlyNoEA"],
			//"gpf_no":["GPF No", "gpfNoEA"],
			
			"app_posting_place":["Place of Posting", "onlyAlphabet"],
			
			"app_headquarter":["Headquarter", "onlyAlphabetEA"],
			"doj":["Date of Joining", "dateEA"],
			
			"dor":["Date of Retirement", "date"],
			
			"office_name":["Name of the Office", "textArea"],
			"office_street":["Address", "streetAddress"],
			"office_city":["City / Town / Village", "onlyAlphabet"],
			
			"office_post_office":["Post Office", "hyphenFullStopEA"],
			
			"office_district":["District", "selectBox"],
			"office_pincode":["Pincode", "onlyNo"],
			
			"office_phone_no":["Telephone No.", "telephoneNoEA"],
			
			"district":["DDO District", "selectBox"],
			"designation":["DDO Designation", "selectBox"],
			
			"rhe_flat_type":["Flat TYPE","flatType"],
			"reason":["Allotment Category", "selectBox"],
			"doa":["Date of Application", "date"],
			"computer_serial_no":["Computer Serial No", "onlyNo"],
			"confirm_computer_serial_no":["Confirm Computer Serial No", "onlyNo"],
			
			"remarks":["Remarks", "textAreaEA"]
			
		};
		
		formElements = jQuery.extend(formElements, formElements2);
		//return formElements;	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}