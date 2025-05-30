//internal date validation function
	function isValidDate(s) {
		// format D(D)/M(M)/(YY)YY
		var dateFormat = /^\d{1,4}[\.|\/|-]\d{1,2}[\.|\/|-]\d{1,4}$/;
	
		if (dateFormat.test(s)) {
			// remove any leading zeros from date values
			s = s.replace(/0*(\d*)/gi,"$1");
			var dateArray = s.split(/[\.|\/|-]/);
		  
				  // correct month value
			dateArray[1] = dateArray[1]-1;
	
			// correct year value
			if (dateArray[2].length<4) {
				// correct year value
				dateArray[2] = (parseInt(dateArray[2]) < 50) ? 2000 + parseInt(dateArray[2]) : 1900 + parseInt(dateArray[2]);
			}
	
			var testDate = new Date(dateArray[2], dateArray[1], dateArray[0]);
			if (testDate.getDate()!=dateArray[0] || testDate.getMonth()!=dateArray[1] || testDate.getFullYear()!=dateArray[2]) {
				return false;
			} else {
				return true;
			}
		} else {
			return false;
		}
	}
	
	function validateOnlyAlphabet(x){
		var onlyAlphabet = document.getElementsByName(x)[0];
		var re = /^[a-zA-Z\s]*$/;
		if(onlyAlphabet.value !== ""){
			if(re.test(onlyAlphabet.value)) {
				onlyAlphabet.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				onlyAlphabet.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			onlyAlphabet.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateAlphabetFullstop(x){
		var alphabetFullstop = document.getElementsByName(x)[0];
		var re = /^[A-Z]+[a-zA-Z\s\.]*$/;
		if(alphabetFullstop.value !== ""){
			if(re.test(alphabetFullstop.value)) {
				alphabetFullstop.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				alphabetFullstop.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			alphabetFullstop.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateDate(x){
		var date = document.getElementsByName(x)[0];
		
		/*var re = /(^(((0[1-9]|1[0-9]|2[0-8])[\/](0[1-9]|1[012]))|((29|30|31)[\/](0[13578]|1[02]))|((29|30)[\/](0[4,6,9]|11)))[\/](19|20)\d\d$)|(^29[\/]02[\/](19|20)(00|04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)$)/;*/
		
		if(date.value !== ""){
			//if(re.test(date.value)) {
			if(isValidDate(date.value)){
				date.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				date.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			date.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateUserName(x){
		var userName = document.getElementsByName(x)[0];
		var re = /^[a-z A-Z 0-9][\.\w]+[a-z A-Z 0-9]$/;
		var n = userName.value.length;
		if(userName.value !== ""){
			if(n >= 5 && n <= 20) {
				if(re.test(userName.value)) {
					userName.style.border ='1px solid #ccc';  
					return true;
				}
				else{
					userName.style.border ='1px dotted #F00';
					return 2;
				}
			} else {
				userName.style.border ='1px dotted #F00';
				return 3;
			}
		} else{
			userName.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateMobileNo(x){
		var mobileNo = document.getElementsByName(x)[0];
		//var re = /^[\d]{10}$/;
		var re = /^[6789][0-9]{9}$/;
		if(mobileNo.value !== ""){
			if(re.test(mobileNo.value)) {
				mobileNo.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				mobileNo.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			mobileNo.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateTelephoneNo(x){
		var telephoneNo = document.getElementsByName(x)[0];
		var re = /^[0-9]+$/;
		if(telephoneNo.value !== ""){
			if(re.test(telephoneNo.value)) {
				telephoneNo.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				telephoneNo.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			telephoneNo.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateHRMSID(x){
		var hrmsId = document.getElementsByName(x)[0];
		//var re = /^[\d]{10}$/;
		var re = /^[1-9][0-9]{9}$/;
		if(hrmsId.value !== ""){
			if(re.test(hrmsId.value)) {
				hrmsId.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				hrmsId.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			hrmsId.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateOnlyNo(x){
		var onlyNo = document.getElementsByName(x)[0];
		//var re = /^[\d]{10}$/;
		var re = /^[1-9][0-9]*$/;
		if(onlyNo.value !== ""){
			if(re.test(onlyNo.value)) {
				onlyNo.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				onlyNo.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			onlyNo.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validatePassWord(x){
		var passWord = document.getElementsByName(x)[0];
		//var re = /^[a-zA-Z0-9!@#$%^&*_-]+$/;
		var re = /^(?=.*[A-z])(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&])[0-9A-za-zA-Z!@#$%^&]{6,20}$/;
		var n = passWord.value.length;
		if(passWord.value !== ""){
			if(n >= 6 && n <= 20) {
				if(re.test(passWord.value)) {
					passWord.style.border ='1px solid #ccc';  
					return true;
				}
				else{
					passWord.style.border ='1px dotted #F00';
					return 2;
				}
				passWord.style.border ='1px solid #ccc';  
				return true;
			} else {
				passWord.style.border ='1px dotted #F00';
				return 3;
			}
		} else{
			passWord.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validatePassWordIfNotBlank(x){
		var passWordIfNotBlank = document.getElementsByName(x)[0];
		//var re = /^[a-zA-Z0-9!@#$%^&*_-]+$/;
		var re = /^(?=.*[A-z])(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&])[0-9A-za-zA-Z!@#$%^&]{6,20}$/;
		var n = passWordIfNotBlank.value.length;
		
		if(passWordIfNotBlank.value !== ""){
			if(n >= 6 && n <= 20) {
				if(re.test(passWordIfNotBlank.value)) {
					passWord.style.border ='1px solid #ccc';  
					return true;
				}
				else{
					passWordIfNotBlank.style.border ='1px dotted #F00';
					return 2;
				}
			} else {
				passWordIfNotBlank.style.border ='1px dotted #F00';
				return 3;
			}
		}
	}
	
	function validateGPFNo(x){
		var gpfNo = document.getElementsByName(x)[0];
		var re = /^[A-Z a-z]+[\/][A-Z a-z]+[\/][\d]+$/;
		if(gpfNo.value !== ""){
			if(re.test(gpfNo.value)) {
				gpfNo.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				gpfNo.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			gpfNo.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateHyphenFullStop(x){
		var hyphenFullStop = document.getElementsByName(x)[0];
		var re = /^[a-z A-Z 0-9]+[\.\-\w\s]*[a-z A-Z 0-9]$/;
		if(hyphenFullStop.value !== ""){
			if(re.test(hyphenFullStop.value)) {
				hyphenFullStop.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				hyphenFullStop.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			hyphenFullStop.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateHyphenFullStopAmpersand(x){
		var hyphenFullStopAmpersand = document.getElementsByName(x)[0];
		var re = /^[a-z A-Z]+[\.\-\&\,\w\s]*[a-z A-Z 0-9 \.]$/;
		if(hyphenFullStopAmpersand.value !== ""){
			if(re.test(hyphenFullStopAmpersand.value)) {
				hyphenFullStopAmpersand.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				hyphenFullStopAmpersand.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			hyphenFullStopAmpersand.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateFrontSlash(x){
		var frontSlash = document.getElementsByName(x)[0];
		var re = /^\w*[\w\/]*\w$/;
		if(frontSlash.value !== ""){
			if(re.test(frontSlash.value)) {
				frontSlash.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				frontSlash.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			frontSlash.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateFrontSlashHyphen(x){
		var frontSlashHyphen = document.getElementsByName(x)[0];
		var re = /^\w*[\w\/\-]*\w$/;
		if(frontSlashHyphen.value !== ""){
			if(re.test(frontSlashHyphen.value)) {
				frontSlashHyphen.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				frontSlashHyphen.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			frontSlashHyphen.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateStreetAddress(x){
		var streetAddress = document.getElementsByName(x)[0];
		var re = /^[a-zA-Z0-9][\.\-\/\,\w\s]+[a-zA-Z0-9]*$/;
		if(streetAddress.value !== ""){
			if(re.test(streetAddress.value)) {
				streetAddress.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				streetAddress.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			streetAddress.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateHousingAddress(x){
		var housingAddress = document.getElementsByName(x)[0];
		var re = /^[a-zA-Z0-9][\.\-\/\,\w\s]+[a-zA-Z0-9]*$/;
		if(housingAddress.value !== ""){
			if(re.test(housingAddress.value)) {
				housingAddress.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				housingAddress.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			housingAddress.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateNo(x){
		var no = document.getElementsByName(x)[0];
		var re = /^[a-zA-Z0-9][\-\w]+[0-9]*$/;
		if(no.value !== ""){
			if(re.test(no.value)) {
				no.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				no.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			no.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateFlatType(x){
		var flatType = document.getElementsByName(x)[0];
		var re = /^[A-Z]+[\+]*$/;
		if(flatType.value !== ""){
			if(re.test(flatType.value)) {
				flatType.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				flatType.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			flatType.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateFlatNo(x){
		var flatNo = document.getElementsByName(x)[0];
		var re = /^[\w\/\-]+$/;
		if(flatNo.value !== ""){
			if(re.test(flatNo.value)) {
				flatNo.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				flatNo.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			flatNo.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	function validateAlphanumeric(x){
		var alphaNumeric = document.getElementsByName(x)[0];
		var re = /^[\w]+$/;
		if(alphaNumeric.value !== ""){
			if(re.test(alphaNumeric.value)) {
				alphaNumeric.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				alphaNumeric.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			alphaNumeric.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	
	function validateFile(x){
	  var allowedFiles = [".pdf"];
	  var fileUpload = document.getElementsByName(x)[0];
	  if(fileUpload.value !== "" ){
		fileUpload.style.border ='1px solid #ccc';  
		return true;
		 /*var regex = new RegExp("([a-zA-Z0-9\s_\\.\-:])+(" + allowedFiles.join('|') + ")$");
			if (!regex.test(fileUpload.value.toLowerCase())) {
				fileUpload.style.border ='1px dotted #F00';
				return 2;
			}else{
			  fileUpload.style.border ='1px solid #ccc';  
			  return true;
			}*/
	  } else{
		fileUpload.style.border ='1px dotted #F00';
		return false;
	  }
	}
	function validateText(x){
		// Validation rule
		var re = /[A-Za-z -']$/;
		// Check input
		if(re.test(document.getElementsByName(x)[0].value)){
			document.getElementsByName(x)[0].style.border ='1px solid #ccc';  
			return true;
		}	else{
			document.getElementsByName(x)[0].style.border ='1px dotted #F00';
			return false;
		}
	}
	function validateTextbox(x){      
		// Check input
		if(document.getElementsByName(x)[0].value != ""){
			document.getElementsByName(x)[0].style.border ='1px solid #ccc';  
			return true;
		}	else{
			document.getElementsByName(x)[0].style.border ='1px dotted #F00';
			return false;
		}
	}
	// Validate email
	function validateEmail(x){
		var re = /^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$/;
		var email = document.getElementsByName(x)[0];
		if(email.value !== ""){
			if(re.test(email.value)) {
				email.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				email.style.border ='1px dotted #F00';
				return 2;
			}
		 
		} else{
			email.style.border ='1px dotted #F00';
			return false;
		}
	}
	function validateTextarea(x){
		var textArea = document.getElementsByName(x)[0];
		var re = /^[\w][-\/()\[\]\{\}\.\,\&\’\'\"\w\s]+$/;
		if(textArea.value !== ""){
			if(re.test(textArea.value)) {
				textArea.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				textArea.style.border ='1px dotted #F00';
				return 2;
			}
		} else{
			textArea.style.border ='1px dotted #F00';
			return false;
		}
	}
	
	// Validate Select boxes
	function validateSelect(x){
		if(document.getElementsByName(x)[0].value !== "" && document.getElementsByName(x)[0].value !== "_none"){
			document.getElementsByName(x)[0].style.border ='1px solid #ccc';  
			return true;
		}	else{
			document.getElementsByName(x)[0].style.border ='1px dotted #F00';
			return false;
		}
	}
	function validateRadio(x){
		var len = document.getElementsByName(x).length;
		var checked = false;
		for(i=0; i<len; i++) {
			if(document.getElementsByName(x)[i].checked){	
				checked = true;
				return true;
			}
		}
		if(!checked) {
			document.getElementsByName(x)[0].style.outline ='1px dotted #F00';
			return false;
		}
	}
	function validateCheckbox(x){
		if(document.getElementsByName(x)[0].checked){
			return true;
		}
		return false;
	}
	

//for existing applicant only
	function validateMobileNoEA(x){
		var mobileNoEA = document.getElementsByName(x)[0];
		//var re = /^[\d]{10}$/;
		var re = /^[6789][0-9]{9}$/;
		if(mobileNoEA.value !== ""){
			if(re.test(mobileNoEA.value)) {
				mobileNoEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				mobileNoEA.style.border ='1px dotted #F00';
				return 2;
			}
		}
	}
	function validateEmailAddressEA(x){
		var re = /^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$/;
		var emailEA = document.getElementsByName(x)[0];
		if(emailEA.value !== ""){
			if(re.test(emailEA.value)) {
				emailEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				emailEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}
	function validateOnlyNoEA(x){
		var onlyNoEA = document.getElementsByName(x)[0];
		//var re = /^[\d]{10}$/;
		var re = /^[1-9][0-9]+$/;
		if(onlyNoEA.value !== ""){
			if(re.test(onlyNoEA.value)) {
				onlyNoEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				onlyNoEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}
	function validateGPFNoEA(x){
		var gpfNoEA = document.getElementsByName(x)[0];
		var re = /^[A-Z a-z]+[\/][A-Z a-z]+[\/][\d]+$/;
		if(gpfNoEA.value !== ""){
			if(re.test(gpfNoEA.value)) {
				gpfNoEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				gpfNoEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}
	function validateOnlyAlphabetEA(x){
		var onlyAlphabetEA = document.getElementsByName(x)[0];
		var re = /^[a-zA-Z\s]*$/;
		if(onlyAlphabetEA.value !== ""){
			if(re.test(onlyAlphabetEA.value)) {
				onlyAlphabetEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				onlyAlphabetEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}
	function validateDateEA(x){
		var dateEA = document.getElementsByName(x)[0];
		
		/*var re = /(^(((0[1-9]|1[0-9]|2[0-8])[\/](0[1-9]|1[012]))|((29|30|31)[\/](0[13578]|1[02]))|((29|30)[\/](0[4,6,9]|11)))[\/](19|20)\d\d$)|(^29[\/]02[\/](19|20)(00|04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)$)/;*/
		
		if(dateEA.value !== ""){
			//if(re.test(dateEA.value)) {
			if(isValidDate(dateEA.value)){
				dateEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				dateEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}
	function validateHyphenFullStopEA(x){
		var hyphenFullStopEA = document.getElementsByName(x)[0];
		var re = /^[a-z A-Z 0-9][\.\-\w]+[a-z A-Z 0-9]$/;
		if(hyphenFullStopEA.value !== ""){
			if(re.test(hyphenFullStopEA.value)) {
				hyphenFullStopEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				hyphenFullStopEA.style.border ='1px dotted #F00';
				return 2;
			}
		}
	}
	function validateTextareaEA(x){
		var textAreaEA = document.getElementsByName(x)[0];
		var re = /^[\w][-\/()\[\]\{\}\.\,\&\’\'\"\w\s]+$/;
		if(textAreaEA.value !== ""){
			if(re.test(textAreaEA.value)) {
				textAreaEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				textAreaEA.style.border ='1px dotted #F00';
				return 2;
			}
		}
	}
	function validateStreetAddressEA(x){
		var streetAddressEA = document.getElementsByName(x)[0];
		var re = /^[a-zA-Z0-9][\.\-\/\,\w\s]+[a-zA-Z0-9]*$/;
		if(streetAddressEA.value !== ""){
			if(re.test(streetAddressEA.value)) {
				streetAddressEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				streetAddressEA.style.border ='1px dotted #F00';
				return 2;
			}
		}
	}
	function validateHRMSIDEA(x){
		var hrmsIdEA = document.getElementsByName(x)[0];
		//var re = /^[\d]{10}$/;
		var re = /^[1-9][0-9]{9}$/;
		if(hrmsIdEA.value !== ""){
			if(re.test(hrmsIdEA.value)) {
				hrmsIdEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				hrmsIdEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}
	function validateTelephoneNoEA(x){
		var telephoneNoEA = document.getElementsByName(x)[0];
		var re = /^[0-9]+$/;
		if(telephoneNoEA.value !== ""){
			if(re.test(telephoneNoEA.value)) {
				telephoneNoEA.style.border ='1px solid #ccc';  
				return true;
			}
			else{
				telephoneNoEA.style.border ='1px dotted #F00';
				return 2;
			}
		 
		}
	}

	

function validateForm(formElements) {
	var error = 0;
	jQuery('#main-content-inside > .error').remove();
	var errorMsg = '<div class="messages error"><h2 class="element-invisible">Error message</h2><ul>';
	
	for (var elementName in formElements) {
		if (formElements.hasOwnProperty(elementName)) {
			if(document.getElementsByName(elementName)[0]) {
			var elementTitle = formElements[elementName][0];	
			var elementType = formElements[elementName][1];
				if(elementType == "selectBox") {				
					if(!validateSelect(elementName)){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				} 
				else if(elementType == "textBox") {
					if(!validateTextbox(elementName)){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				} 
				else if(elementType == "radioBox") {
					if(!validateRadio(elementName)){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				} 
				else if(elementType == "checkBox") {
					if(!validateCheckbox(elementName)){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				} 
				else if(elementType == "fileUpload") {
					if(!validateFile(elementName)){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				
				else if(elementType == "onlyAlphabet") {
					var res=validateOnlyAlphabet(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabatic.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "alphabetFullstop") {
					var res=validateAlphabetFullstop(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabatic.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "date") {
					var res=validateDate(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be DD/MM/YYYY format.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "userName") {
					var res=validateUserName(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphnumeric. Only special characters _ . allowed.</li>';
						error++;
					}
					else if(res==3) {
						errorMsg = errorMsg+'<li>'+elementTitle+' must be between 5 to 20 characters.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "mobileNo") {
					var res=validateMobileNo(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be 10 digits.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "telephoneNo") {
					var res=validateTelephoneNo(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be digits.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "hrmsId") {
					var res=validateHRMSID(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be 10 digits.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "emailAddress") {
					var res=validateEmail(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' is not valid.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "onlyNo") {
					var res=validateOnlyNo(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be numeric.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "gpfNo") {
					var res=validateGPFNo(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be ADM/WB/00000 format.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "hyphenFullStop") {
					var res=validateHyphenFullStop(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic. Only special characters . - allowed. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "hyphenFullStopAmpersand") {
					var res=validateHyphenFullStopAmpersand(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic. Only special characters . - & allowed. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "frontSlash") {
					var res=validateFrontSlash(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic or alphanumeric. Only special characters / allowed. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "frontSlashHyphen") {
					var res=validateFrontSlashHyphen(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic or alphanumeric. Only special characters / and - allowed. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "streetAddress") {
					var res=validateStreetAddress(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphanumeric. Only special characters . , - / allowed. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "housingAddress") {
					var res=validateHousingAddress(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphanumeric. Only special characters . , - / allowed. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "no") {
					var res=validateNo(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphnumeric. Only special characters - allowed.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "flatType") {
					var res=validateFlatType(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic. Only special characters + allowed.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "flatNo") {
					var res=validateFlatNo(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphnumeric. Only special characters - and / allowed.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				else if(elementType == "alphaNumeric") {
					var res=validateAlphanumeric(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphnumeric.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				
				else if(elementType == "passWord") {
					var res=validatePassWord(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must contains at least one lowercase character, one uppercase character, one digit from 0-9 and one special symbols in this list ! @ # $ % ^ and &.</li>';
						error++;
					}
					else if(res==3){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be between 6 to 20 characters.</li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}					
				}
				
				else if(elementType == "passWordIfNotBlank") {
					var res=validatePassWordIfNotBlank(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must contains at least one lowercase character, one uppercase character, one digit from 0-9 and one special symbols in this list ! @ # $ % ^ and &.</li>';
						error++;
					}
					else if(res==3){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be between 6 to 20 characters.</li>';
						error++;
					}					
				}
				
				else if(elementType == "textArea") {
					var res=validateTextarea(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic. Use proper special characters. </li>';
						error++;
					}
					else if(!res){
						errorMsg = errorMsg+'<li>'+elementTitle+' field is required.</li>';
						error++;
					}				
				}
				
				
				//for existing applicant only
				else if(elementType == "mobileNoEA") {
					var res=validateMobileNoEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be 10 digits.</li>';
						error++;
					}				
				}
				else if(elementType == "emailAddressEA") {
					var res=validateEmailAddressEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' is not valid.</li>';
						error++;
					}				
				}
				else if(elementType == "onlyNoEA") {
					var res=validateOnlyNoEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be numeric.</li>';
						error++;
					}				
				}
				else if(elementType == "gpfNoEA") {
					var res=validateGPFNoEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be ADM/WB/00000 format.</li>';
						error++;
					}				
				}
				else if(elementType == "onlyAlphabetEA") {
					var res=validateOnlyAlphabetEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabatic.</li>';
						error++;
					}					
				}
				else if(elementType == "dateEA") {
					var res=validateDateEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be DD/MM/YYYY format.</li>';
						error++;
					}				
				}
				else if(elementType == "hyphenFullStopEA") {
					var res=validateHyphenFullStopEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic. Only special characters . - allowed. </li>';
						error++;
					}				
				}
				else if(elementType == "textAreaEA") {
					var res=validateTextareaEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphabetic. Use proper special characters. </li>';
						error++;
					}				
				}
				else if(elementType == "streetAddressEA") {
					var res=validateStreetAddressEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphanumeric. Only special characters . , - / allowed. </li>';
						error++;
					}				
				}
				else if(elementType == "hrmsIdEA") {
					var res=validateHRMSIDEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be alphanumeric. Only special characters . , - / allowed. </li>';
						error++;
					}				
				}
				else if(elementType == "telephoneNoEA") {
					var res=validateTelephoneNoEA(elementName);
					if(res==2){
						errorMsg = errorMsg+'<li>'+elementTitle+' must be digits.</li>';
						error++;
					}				
				}			
			}
		}
	}
		
	if(error > 0){
		errorMsg = errorMsg+'</ul></div>';
		jQuery('#main-content-inside').prepend(errorMsg);
		return false;
	} else {
		return true;
	}
}

