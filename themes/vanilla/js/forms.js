(function($) {

    Drupal.behaviors.vanillaForms = {
        attach: function(cx, s) {
            if (!!$.fn.chosen) {
                $('select').chosen({
                    disable_search_threshold: 10
                });
            }

            if (!!$.fn.customFileInput) {
                $('input[type="file"]').customFileInput();
            }

            $('form').submit(function() {
                $(this).addClass('processing');
            });
        }
    }

})(jQuery);
