(function($) {

    Drupal.behaviors.vanilla = {
        attach: function(cx, s) {
            $(window).load(function() {
                $('html').addClass('loaded');
            });
        }
    }

})(jQuery);
