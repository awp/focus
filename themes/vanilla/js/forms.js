(function($) {

    Drupal.behaviors.vanillaForms = {
        attach: function(cx, s) {

            if (!!$.fn.customFileInput) {
                $('input[type="file"]').customFileInput();
            }

            if (!!$.fn.placeholder) {
                $('input, textarea').placeholder();
            }

            $('form').submit(function() {
                $(this).addClass('processing');
            });
        }
    }

})(jQuery);
