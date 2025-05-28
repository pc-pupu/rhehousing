	
	function validate_applicant_data_upload_form(){
		var formElements =
		{
			"files[applicant_data_excel_file]":["Upload Applicant Data","fileUpload"],
		};
			
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
		
	}