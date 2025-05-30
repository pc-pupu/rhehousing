jQuery(document).ready(function(){
var checkboxes = jQuery(".form-item").children(".form-checkbox");

    if ( checkboxes.filter( ':checked' ).length == checkboxes.length )      
		
		jQuery(".select-all").children(".form-checkbox").attr('checked', 'checked');
		
});

