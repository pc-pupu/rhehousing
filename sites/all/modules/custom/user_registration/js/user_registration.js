//dj = jQuery.noConflict();
/*jQuery(document).ready(function(){
	jQuery("#dob").datepicker({
    dateFormat: "dd/mm/yy",
    changeMonth: true,
    changeYear: true,
    autoSize: true
   });
   });*/

/*	function numbersonly(e){
		var unicode=e.charCode? e.charCode : e.keyCode
		if (unicode!=8){ //if the key isn't the backspace key (which we should allow)
			if (unicode<48||unicode>57) //if not a number
				return false //disable key press
		}
	}   */
	
	/*jQuery(document).ready(function() {
		jQuery("#edit-dob").datepicker({
			dateFormat: "dd/mm/yy",
			changeMonth: true,
			changeYear: true,
			//yearRange: "-70:+0",
			yearRange: "-70:-18", //18 years or older up to 70year (oldest person ever, can be sensibly set to something much smaller in most cases)
		    maxDate: "-18Y", //Will only allow the selection of dates more than 18 years ago, useful if you need to restrict this
		    minDate: "-70Y",
			autoSize: true
		});
	});

	jQuery(document).ready(function() {
	
		jQuery("#mobile_no").keypress(function (e)  
		{ 
		  if( e.which!=8 && e.which!=0 && (e.which<48 || e.which>57))
		  {
			return false;
		  }	
		});
		
	});*/
	
	function validate_applicant_regform(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"applicant_name":["Applicant Name","alphabetFullstop"],
			"dob":["Date of Birth","date"],
			"gender":["Gender", "radioBox"],
			//"username":["Username", "userName"],
			"mobile":["Mobile No", "mobileNo"],
			"email":["Email Id", "emailAddress"],
			"hrms_id":["Employee HRMS ID", "hrmsId"],
			"app_designation":["Designation", "textArea"],
			"office_name":["Name of the Office", "textArea"],
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	
	/*function validate_applicant_regform_upload(){
		var formElements =
		{
			"registration_id":["Registration Id", "onlyNo"],
			"files[applicant_regform_file]":["Upload Applicant Registration Form","fileUpload"]
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}*/
  