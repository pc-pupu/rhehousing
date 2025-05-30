jQuery( function() {
    jQuery( '#sortable > tbody' ).sortable();
  } );

jQuery( function() {
  jQuery('#savebtn').click(function(){
  var array=[];
  jQuery.each(jQuery('#sortable >tbody').find('tr'),function(){
    array.push(jQuery(this).data('id'));
  });
  jQuery('#online_app_ids').val(array.toString());
  jQuery('#special-recommendation-list-view-form').submit();
  });
} );




