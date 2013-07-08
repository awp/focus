(function($) {

    Drupal.behaviors.simplicity = {
        attach: function(cx, s) {
            if (!!$('select').chosen) {
                $('select').chosen({
                    width: "100%",
                    disable_search_threshold: 10
                });
            }
        }
    }

})(jQuery);
