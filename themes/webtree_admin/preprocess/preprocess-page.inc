<?php
// RFC2822 date format
if ($rfc = date("r" , time())) {
    $vars['datetime_rfc'] = t('@time', array('@time' => $rfc));
}
else {
    $rfc = '';
    $vars['datetime_rfc'] = '';
}
// ISO 8601 date format
if ($iso = gmdate('Y-m-d\TH:i:sO')) {
    $vars['datetime_iso'] = $iso;
}
else {
    $iso = '';
    $vars['datetime_iso'] = '';
}

$vars['content_header_attributes_array']['class'][] = 'branding-elements';
$vars['content_header_attributes_array']['role'][] = 'banner';
