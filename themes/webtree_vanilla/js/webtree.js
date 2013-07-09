(function($){

    var webtreeInit = function(cx, s) {
        $('body').once('webtree-colorbox', function() {
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

    Drupal.behaviors.webtree = {
        attach: webtreeInit
    }

    if (!!Drupal.settings.colorbox) {
        Drupal.settings.colorbox.title = function() {
            var title = $(this).attr('title');
            var html  = '<table cellspacing="0"><tr><td>'+title+'</td></tr></table>';
            return (!title) ? false : html;
        }
    }

})(jQuery);
