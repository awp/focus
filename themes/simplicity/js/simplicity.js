(function($) {

    Drupal.behaviors.simplicity = {
        attach: function(cx, s) {
            if (!!$('select').chosen) {
                $('select').chosen();
            }
        }
    }

})(jQuery);
