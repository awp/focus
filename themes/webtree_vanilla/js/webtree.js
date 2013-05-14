(function($){
    
    var webtreeInit = function(cx, s) {
        
        $('#page', cx).once('webtree-init', function() {
            console.log('WebTree Init');
        });
        
        
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
            var title = '<table cellspacing="0"><tr><td>'+$(this).attr('title')+'</td></tr></table>'; 
            return (!$(this).attr('title')) ? false : title;
        }
    }

})(jQuery);
