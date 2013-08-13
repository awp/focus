(function($) {

    Drupal.behaviors.vanillaChosen = {
        attach: function(cx, s) {
            if (!!$('select').chosen) {
                $('select').chosen({
                    disable_search_threshold: 10
                });
            }
        }
    }

})(jQuery);
