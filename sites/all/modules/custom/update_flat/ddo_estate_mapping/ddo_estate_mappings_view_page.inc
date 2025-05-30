<?php
/**
 * Callback function for Popup page.
 */
function view_fss_price_page($js, $fssPriceTypeID)
{
    $output = get_fss_price_details($fssPriceTypeID);
    //$output = drupal_render(get_fss_price_details($fssPriceTypeID));
    
    if ($js) {
        // Required includes for ctools to work:
        ctools_include('modal');
        ctools_include('ajax');
        return ctools_modal_render("Fss Breed Price Details", $output);
    }
    return $output;
}

function get_fss_price_details($fssPriceTypeID = NULL)
{
    global $base_url;
    
    $fssPriceTypeID = base64_decode($fssPriceTypeID);
    
    $query = db_select(PBGSBS_FSS_PRICE_TYPE, "pfi");
    $query->join(PBGSBS_FSS_BREEDWISE_PRICE, 'pfid', 'pfi.id= pfid.fss_price_type_id');
    $query->join("pbgsbs_ai_animal_breed", "aab", 'pfid.animal_breed_id= aab.animal_breed_id');
    $query->join('pbgsbs_ai_animal_type', 'aat', 'aab.animal_type_id= aat.animal_type_id');
    
    // Adding fields
    $query->fields('pfi',array('price_type'));
    $query->fields('pfid');
    $query->fields('aab', array(
        'animal_breed',
        'animal_breed_code',
        'animal_breed_id'
    ));
    $query->fields('aat', array(
        'animal_type'
    ));
    
    $query->orderBy('pfi.created_date', 'DESC');
    
    $query->condition('pfi.id', $fssPriceTypeID, '=');
    
    // Executing query
    $result = $query->execute();
    
    $sl_no      = 0;
    $varLastRow = NULL;
    $header     = array(
        'slno' => array(
            'data' => 'Sl. No.'
        ),
        'animal_type' => array(
            'data' => 'Animal Type'
        ),
        'animal_breed' => array(
            'data' => 'Breed'
        ),
        'price' => array(
            'data' => 'Price'
        )
    );
    $rows       = array();
    while ($data = $result->fetchObject()) {
        $varLastRow = $data;
        $sl_no++;
        $rows[$data->id] = array(
            'slno' => $sl_no,
            'animal_type' => ucfirst($data->animal_type),
            'animal_breed' => $data->animal_breed . ' (' . $data->animal_breed_code . ')',
            'price' => $data->price
        );
    }
    
    $output_challan = theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'caption' => '<h2>Breedwise Price Details of '.$varLastRow->price_type.'</h2>',
        'sticky' => TRUE,
        'empty' => 'No data found!',
        'attributes' => array(
            'class' => array(
                'challan-details-table'
            ),
            'width' => "100%",
            'align' => "center"
        )
    ));
    
    
    $data = $varLastRow;
   
    //$indentFromTxt = $data->indent_from==1 ? ucfirst($data->kitbank_name).' Kitbank':($data->indent_from==2 ? ucfirst($data->districtname).' District' : ucfirst($data->blockname).' Block');
    
    /*$htmlOP = '<div id="DivToPrintChallan">
<table width="80%" border="0" cellspacing="2" cellpadding="2"  id="kitbank_challan" align="center" style="font-family: Cambria, Georgia, Palatino, Times New Roman, serif;">
  <tr>
    <td colspan="2" style="padding: 8px;"><table width="100%" border="0" align="center" cellpadding="2" cellspacing="2">
      <tbody style="border:none;">
      <tr>
        <td width="15%"><img src="' . $base_url . '/' . drupal_get_path("theme", "pms") . '/images/report-logo.png" width="110"/></td>
        <td width="85%" align="center" style="padding-left:0px;"><span style="font-size:22px;">Paschim Banga Go-Sampad Bikash Sanstha</span> <br />
<span style="font-size:18px;">(A Govt. of West Bengal Organisation) </span><br />
<span style="font-size:20px;"><strong>' . ucfirst($indentFromTxt) . '</strong></span><br /><br />
<span style="font-size:20px;"><strong>INDENT DETAILS</strong></span></td>
      </tr></tbody>
    </table></td>
  </tr>
   <tr>
    <td width="50%" align="left" style="padding: 8px;"><strong>No: &nbsp; </strong>' . $data->indent_id . '</td>
    <td width="50%" align="left" style="padding: 8px; "><strong>Date: </strong>' . $data->created_date . '</td>
  </tr>
   <!--<tr>
    <td width="50%" align="left" style="padding: 8px;"><strong>To: &nbsp; </strong></td>
    <td width="50%" style="padding: 8px; ">&nbsp;</td>
  </tr>-->
   <tr>
    <td width="50%" align="left" style="padding: 8px;"><strong>Ref. No: &nbsp;</strong>' . $data->indent_ref_no . '</td>
    <!--<td width="50%" align="left" style="padding: 8px; "><strong>Date: &nbsp;</strong></td>-->
  </tr>
   <tr>
    <td colspan="2" align="left" style="padding: 8px;">' . $output_challan . '</td>
  </tr>  
  <tr>
    <td width="50%" align="left" style="padding: 8px;">Please sign &amp; return in duplicate with seal.</td>
    <td width="50%" align="left" style="padding: 8px; ">&nbsp;</td>
  </tr>
  <tr>
    <td width="50%" style="padding: 8px;">&nbsp;</td>
    <td width="50%" style="padding: 8px; ">&nbsp;</td>
  </tr>
    <tr>
    <td width="70%" style="padding: 8px;">&nbsp;</td>
    <td width="30%" align="right" style="padding: 8px; "><strong>Signature:</strong></td>
  </tr>
  
</table></div><div style="text-align:left; margin-left:90px; ">' . l(t('<img src="' . drupal_get_path('module', 'common_var') . '/images/print.png' . '" width="32" height="32" title="Print">'), 'javascript:', array(
        'external' => TRUE,
        'attributes' => array(
            'onclick' => 'return fssChallanPrint()'
        ),
        'html' => TRUE
    )) . '</div>';*/
    return $output_challan;
}