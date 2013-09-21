(function($){

    Drupal.behaviors.vanillaColorbox = {
        attach: function (cx, s) {
            $('body').once('vanilla-colorbox', function() {
                $(window).bind({
                    cbox_load: function() {
                        $('html').addClass('colorbox-open');
                    },
                    cbox_cleanup: function() {
                        $('html').removeClass('colorbox-open');
                    }
                });
            });
        }
    }

    if (!!Drupal.settings.colorbox) {
        Drupal.settings.colorbox.title = function() {
            var title = $(this).attr('title');
            var html  = '<table cellspacing="0"><tr><td>'+title+'</td></tr></table>';
            return (!title) ? false : html;
        }
    }

})(jQuery);
