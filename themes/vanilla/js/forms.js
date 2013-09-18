(function($) {

    Drupal.behaviors.vanillaChosen = {
        attach: function(cx, s) {
            if (!!$.fn.chosen) {
                $('select').chosen({
                    disable_search_threshold: 10
                });
            }

            if (!!$.fn.customFileInput) {
                $('input[type="file"]').customFileInput();
            }
        }
    }

})(jQuery);
