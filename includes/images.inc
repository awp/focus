<?php
/**
 * @file
 * Contains functions providing default image configurations.
 */

/**
 * Implements hook_image_default_styles().
 */
function focus_image_default_styles() {
    $styles['inline'] = array(
        'effects' => array(
            array(
                'label' => 'Scale',
                'name' => 'image_scale',
                'data' => array(
                    'width' => '',
                    'height' => 320,
                    'upscale' => 1,
                ),
            ),
        ),
    );
    
    $styles['slideshow'] = array(
        'effects' => array(
            array(
                'label' => 'Scale',
                'name' => 'image_scale',
                'data' => array(
                    'width' => 1600,
                    'height' => '',
                    'upscale' => 1,
                ),
            ),
            array(
                'label' => 'Crop',
                'name' => 'image_crop',
                'data' => array(
                    'height' => 540,
                    'width' => 1600,
                    'anchor' => 'center-center',
                    'retinafy' => 1,
                ),
            ),
        ),
    );

    $styles['small'] = array(
        'effects' => array(
            array(
                'label' => 'Scale',
                'name' => 'image_scale',
                'data' => array(
                    'width' => 360,
                    'height' => '',
                    'upscale' => 1,
                    'retinafy' => 1,
                ),
            ),
        ),
    );
    
    $styles['square_thumbnail'] = array(
        'effects' => array(
            array(
                'label' => 'Scale',
                'name' => 'image_scale',
                'data' => array(
                    'width' => 140,
                    'height' => '',
                    'upscale' => 1,
                ),
            ),
            array(
                'label' => 'Crop',
                'name' => 'image_crop',
                'data' => array(
                    'height' => 140,
                    'width' => 140,
                    'anchor' => 'center-center',
                    'retinafy' => 1,
                ),
            ),
        ),
    );

    return $styles;
}

/**
 * Implements hook_image_styles_alter()
 */
function focus_image_styles_alter(&$styles) {
    if ($styles['thumbnail']['storage'] == IMAGE_STORAGE_DEFAULT) {
        $styles['thumbnail']['effects'] = array(
            array(
                'label' => 'Scale',
                'name' => 'image_scale',
                'data' => array(
                    'height' => 140,
                    'width' => 140,
                    'upscale' => 1,
                    'retinafy' => 1,
                ),
                'weight' => 0,
                'effect callback' => 'image_scale_effect',
            ),
        );
    }
    
    if ($styles['square_thumbnail']['storage'] == IMAGE_STORAGE_DEFAULT) {        
        $styles['square_thumbnail']['effects'] = array(
            array(
                'label' => 'Scale & Crop',
                'name' => 'image_scale_and_crop',
                'data' => array(
                    'width' => 140,
                    'height' => 140,
                    'retinafy' => 1,
                ),
                'weight' => 0,
                'effect callback' => 'image_scale_and_crop_effect',
            ),
        );
    }
  
    if ($styles['medium']['storage'] == IMAGE_STORAGE_DEFAULT) {
        $styles['medium']['effects'] = array(
            array(
                'label' => 'Scale & Crop',
                'name' => 'image_scale_and_crop',
                'data' => array(
                    'width'  => 540,
                    'height' => 540,
                    'retinafy' => 1,
                ),
                'weight' => 0,
                'effect callback' => 'image_scale_and_crop_effect',
            ),
        );
    }

    if ($styles['large']['storage'] == IMAGE_STORAGE_DEFAULT) {
        $styles['large']['effects'] = array(
            array(
                'label' => 'Scale & Crop',
                'name' => 'image_scale_and_crop',
                'data' => array(
                    'width'  => 760,
                    'height' => 760,
                    'retinafy' => 1,
                ),
                'weight' => 0,
                'effect callback' => 'image_scale_and_crop_effect',
            ),
        );
    }
}
