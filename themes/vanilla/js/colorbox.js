(function($){

    Drupal.behaviors.vanillaColorbox = {
        attach: function (cx, s) {
            $('body').once('vanilla-colorbox', function() {
                $(window).bind({
                    cbox_load: function() {
                        $('body').addClass('colorbox-open');
                    },
                    cbox_cleanup: function() {
                        $('body').removeClass('colorbox-open');
                    }
                });
            });
        }
    }

    if (!!Drupal.settings.colorbox) {
        Drupal.settings.colorbox.title = function() {
            var title = '<table cellspacing="0"><tr><td>'+$(this).attr('title')+'</td></tr></table>';
            return (!$(this).attr('title')) ? false : title;
        }
    }

})(jQuery);
