(function () {
    // more or less stolen form jquery core and adapted by paul irish
    function getScript(url, success) {
        var script = document.createElement('script');
        script.src = url;
        var head = document.getElementsByTagName('head')[0],
            done = false;
        //alert("head" + head)
        script.onload =  function () {
            //alert(2);
            if (!done && (!this.readyState
                || this.readyState == 'loaded'
                || this.readyState == 'complete')) {
                done = true;
                success();
                script.onload = script.onreadystatechange = null;
                head.removeChild(script);
            }
        };
        head.appendChild(script);
    }
    getScript('https://cdn.bootcss.com/jquery/1.10.2/jquery.min.js', function () {
        if (typeof jQuery == 'undefined') {
            alert('Sorry, but jQuery wasn\'t able to load');
        } else {
            //alert('This page is now jQuerified with v' + $.fn.jquery);
            $(document).ready(function () {

            });
        }
    });
})();