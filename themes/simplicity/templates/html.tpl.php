<?php
/**
 * @file
 * Returns the HTML for the basic html structure of a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728208
 */
?><!DOCTYPE html>
<!--[if IEMobile 7]><html class="iem7" <?= $html_attributes; ?>><![endif]-->
<!--[if lte IE 6]><html class="lt-ie9 lt-ie8 lt-ie7" <?= $html_attributes; ?>><![endif]-->
<!--[if (IE 7)&(!IEMobile)]><html class="lt-ie9 lt-ie8" <?= $html_attributes; ?>><![endif]-->
<!--[if IE 8]><html class="lt-ie9" <?= $html_attributes; ?>><![endif]-->
<!--[if (gte IE 9)|(gt IEMobile 7)]><!--><html <?= $html_attributes . $rdf_namespaces; ?>><!--<![endif]-->

<head>
  <?= $head; ?>
  <title><?= $head_title; ?></title>
  <?= $styles; ?>
  <?= $scripts; ?>
</head>
<body class="<?= $classes; ?>" <?= $attributes;?>>
  <?= $page_top; ?>
  <?= $page; ?>
  <?= $page_bottom; ?>
</body>
</html>
