[% USE raw %]
[% USE Koha %]
[% USE Branches %]
[% USE Categories %]
[% USE ItemTypes %]
[% USE KohaNews %]
[% PROCESS 'html_helpers.inc' %]
[% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
[% SET OpacHeader = KohaNews.get( location => "opacheader", lang => lang, library => branchcode, blocktitle => 0 ) %]
[% SET OpacCustomSearch = KohaNews.get( location => "OpacCustomSearch", lang => lang, library => branchcode, blocktitle
=> 0 ) %]
[% SET OpacLoginInstructions = KohaNews.get( location => "OpacLoginInstructions", lang => lang, library => branchcode )
%]

<div id="wrapper">

    <!-- khakdaman -->
    <div id="header-region" class="noprint row">

        [% IF ( bodyid != 'opac-main' ) %]
        <div class="col-10"></div>
        <div class="col-2">

            <!-- <div class="col-8"> -->
            <nav class="navbar navbar-expand" style="justify-content: left;direction: ltr;">

                <div class="dropdown">
                    <span class="fa fa-list fa-icon-black font-medium-3 dropdown-toggle nav-hide-arrow cursor-pointer"
                        data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" role="menu">
                    </span>
                    <div class="dropdown-menu" style="right: inherit;direction: rtl; padding: 0 0 !important;">

                        <a href="/" class="nav-link p-1 login-link">الصفحة الرئيسية</a>

                        <a href="/cgi-bin/koha/opac-search.pl" class="nav-link p-1 login-link">فريق العمل</a>

                        <a href="/cgi-bin/koha/opac-search.pl " class="nav-link p-1 login-link">البحث المتقدم</a>

                        [% IF Koha.Preference( 'OpacBrowser' ) == 1 %]

                        <a href="/cgi-bin/koha/opac-browser.pl" class="nav-link p-1 login-link">تصفح هرمي</a>
                        [% END %]
                        [% IF Koha.Preference( 'OpacAuthorities' ) == 1 %]

                        <a href="/cgi-bin/koha/opac-authorities-home.pl" class="nav-link p-1 login-link">مكنز
                            المواضيع</a>
                        [% END %]
                        [% IF Koha.Preference( 'TagsEnabled' ) == 1 %]

                        <a href="/cgi-bin/koha/opac-tags.pl" class="nav-link p-1 login-link">سحابة الوسوم</a>
                        [% END %]

                        [% IF Koha.Preference( 'OpacCloud' ) == 1 %]

                        <a href="/cgi-bin/koha/opac-tags_subject.pl" class="nav-link p-1 login-link">سحابة
                            الموضوع</a>
                        [% END %]

                        [% IF Koha.Preference( 'OpacTopissue' ) == 1 %]

                        <a href="/cgi-bin/koha/opac-topissues.pl" class="nav-link p-1 login-link">الأكثر شعبية</a>
                        [% END %]

                        [% IF Koha.Preference('SearchEngine') == 'Elasticsearch' && Koha.Preference( 'OpacBrowseSearch'
                        ) == 1
                        %]

                        <a href="/cgi-bin/koha/opac-browse.pl" class="nav-link p-1 login-link">استعراض البحث</a>
                        [% END %]


                        <a id="library_page" href="/cgi-bin/koha/opac-library.pl" class="nav-link p-1 login-link">
                            [% IF ( singleBranchMode ) %] مكتبة [% ELSE %] المكتبات المشاركة [% END %]
                        </a>

                    </div>
                </div>

            </nav> <!-- /navbar -->
        </div>
        [% IF (0) %]
        <style>
            .topnav {
                overflow: hidden;
                background-color: #03588f;
                display: flex;
                justify-content: center;
                background-image: url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAAwCAMAAADn7eCzAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAA2RpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMC1jMDYwIDYxLjEzNDc3NywgMjAxMC8wMi8xMi0xNzozMjowMCAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0UmVmPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VSZWYjIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtcE1NOk9yaWdpbmFsRG9jdW1lbnRJRD0ieG1wLmRpZDoxRDZGNzgyQUJBMkFFMzExQTVGNUFCRDU2OEZBRUZFNyIgeG1wTU06RG9jdW1lbnRJRD0ieG1wLmRpZDoxQjdGMDY5NjhGRjcxMUU0OEIyREIwQzAwOTQxNzMxMCIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDoxQjVEQTI3MThGRjcxMUU0OEIyREIwQzAwOTQxNzMxMCIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgQ1M1IFdpbmRvd3MiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpENEUxRjg4RjMwOEZFNDExQUIxRkIwQjlDNTdGNDY4OSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDoxRDZGNzgyQUJBMkFFMzExQTVGNUFCRDU2OEZBRUZFNyIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PtZ6eSMAAAB4UExURQAyTwAzUAA2VQA1UwA0UgE8XgJHbwAzUQJIcQE5WQE/YwJDaQFBZQE+YgFAZQFAZAFBZgE7XQE+YQA4VwE9YAJGbQA3VgJEagJFbAJIcAE4WAJEawE9XwE7XAJHbgA1VAA3VwFCZwA0UQJFbQE6WgE6WwFCaAE5Wi89I/YAAABJSURBVHjaLMFZAoEAFADAiSwRKbIUUcL9b9j7MGPtZqlTe7tqXWx99Q5ye4WNncrJ3SKWHj5GP5nG0cvZLD7NYxoHK0n8mwQYALE7AxwrPIzXAAAAAElFTkSuQmCC");
                border-radius: 5px;
                z-index: 1000;
                margin: 0px auto;
                line-height: 250%;
                margin-bottom: -23px;
            }

            .topnav a {
                float: right;
                display: block;
                color: #f2f2f2;
                text-align: center;
                padding: 0px 5px;
                text-decoration: none;
                font-size: 17px;
            }

            .topnav a:not(:first-child) {
                background-color: initial;
            }

            .topnav a:hover {
                background-color: #004f7d;
            }

            .topnav a.active {
                background-color: #04AA6D;
                color: white;
            }

            .topnav .icon {
                display: none;
            }

            /* @media screen and (max-width: 916px) {
            .item-nav-7 {
                display: none !important;
                background-color: #828586 !important;
            }
        }
        @media screen and (max-width: 1052px) {
            .item-nav-9 {
                display: none !important;
                background-color: #828586 !important;
            }
        } */

            .item-nav-14::after {
                content: "" !important;
            }

            @media screen and (max-width: 742px) {
                /* .item-nav-14 ,.item-nav-11 {
                display: none !important;
                background-color: #828586 !important;
            } */

                .topnav a:not(:first-child) {
                    display: none;
                    background-color: #00324f;
                }

                .topnav a:not(:first-child):hover {
                    background-color: #004f7d;
                }

                .topnav a.icon {
                    float: left;
                    display: block;
                }

                .topnav a:after {
                    content: initial;
                }

                .topnav {
                    overflow: hidden;
                    background-color: #08090a;
                    display: inherit;
                    margin-bottom: -16px;
                    z-index: 1000;
                    position: relative;
                    /* height: 49px; */
                }

                .row-nav {
                    display: inherit;
                }


                .first-item-nav {
                    margin-top: 0px !important;
                    padding: 6px 20px !important;
                }

            }

            .main #searchform {
                margin-top: 15px;
            }


            @media screen and (max-width: 1005px) {
                .topnav a {
                    font-size: 1.62vw;
                }
            }

            @media screen and (max-width: 742px) {

                .topnav.responsive {
                    position: relative;

                }


                .topnav.responsive .icon {
                    text-align: left;
                    position: absolute;
                    left: 0px;
                    top: -1px;
                }

                .topnav a {
                    margin-bottom: -6px;
                    padding: 0 20px;
                    font-size: 17px;
                }

                .topnav.responsive a {
                    float: none;
                    display: block;
                    text-align: right;
                    margin-top: -1px;
                    padding: 2px 20px;
                }
            }
        </style>

        <div class="row row-nav" id="DivMyTopnav">
            <div class="topnav" id="myTopnav">
                <!-- khakdaman -->

                <a href="/" class="first-item-nav">الصفحة الرئيسية</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>

                <a href="/cgi-bin/koha/opac-search.pl" class="first-item-nav item-nav-2">فريق العمل</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>

                <a href="/cgi-bin/koha/opac-search.pl " class="first-item-nav item-nav-3">البحث المتقدم</a>

                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% IF Koha.Preference( 'OpacBrowser' ) == 1 %]

                <a href="/cgi-bin/koha/opac-browser.pl" class="first-item-nav item-nav-6">تصفح هرمي</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% END %]
                [% IF Koha.Preference( 'OpacAuthorities' ) == 1 %]

                <a href="/cgi-bin/koha/opac-authorities-home.pl" class="first-item-nav item-nav-7">مكنز المواضيع</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% END %]
                [% IF Koha.Preference( 'TagsEnabled' ) == 1 %]

                <a href="/cgi-bin/koha/opac-tags.pl" class="first-item-nav item-nav-9">سحابة الوسوم</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% END %]

                [% IF Koha.Preference( 'OpacCloud' ) == 1 %]

                <a href="/cgi-bin/koha/opac-tags_subject.pl" class="first-item-nav item-nav-10">سحابة الموضوع</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% END %]

                [% IF Koha.Preference( 'OpacTopissue' ) == 1 %]

                <a href="/cgi-bin/koha/opac-topissues.pl" class="first-item-nav item-nav-11">الأكثر شعبية</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% END %]

                [% IF Koha.Preference('SearchEngine') == 'Elasticsearch' && Koha.Preference( 'OpacBrowseSearch' ) == 1
                %]

                <a href="/cgi-bin/koha/opac-browse.pl" class="first-item-nav item-nav-12">استعراض البحث</a>
                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                [% END %]


                <a id="library_page" href="/cgi-bin/koha/opac-library.pl" class="first-item-nav item-nav-14">
                    [% IF ( singleBranchMode ) %] مكتبة [% ELSE %] المكتبات المشاركة [% END %]
                </a>


                [% IF Koha.Preference( 'suggestion' ) == 1 %]
                [% IF Koha.Preference( 'AnonSuggestions' ) == 1 || Koha.Preference( 'OPACViewOthersSuggestions' ) == 1
                %]

                <a class="first-item-nav between-nav-item" style="background-color: initial;">|</a>
                <a href="/cgi-bin/koha/opac-suggestions.pl?suggested_by_anyone=1"
                    class="first-item-nav item-nav-13">مقترحات
                    الشراء</a>
                [% END %]
                [% END %]

                <!-- 
                
            [% IF ( Koha.Preference( 'UseCourseReserves' ) == 1 ) %]
    
            <a href="/cgi-bin/koha/opac-course-reserves.pl" class="first-item-nav item-nav-5">الحجز الأكاديمي</a>
            [% END %] -->
                <!-- [% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && ( Koha.Preference( 'OPACComments' ) == 1 ) && (Koha.Preference( 'OpacShowRecentComments' ) == 1 ) ) %]
    
            <a href="/cgi-bin/koha/opac-showreviews.pl" class="first-item-nav item-nav-8">التعليقات الأخيرة</a>
            [% END %] -->

                [% Koha.Preference('OpacMoreSearches') | $raw %]
                <a href="javascript:void(0);" class="icon" onclick="myFunction()" style="background-color: revert;">
                    <i class="fa fa-bars mt-2" style="font-size: 35px;"></i>
                </a>
            </div>
        </div>




        <script>
            function myFunction() {
                var x = document.getElementById("myTopnav");
                if (x.className === "topnav") {
                    x.className += " responsive";
                } else {
                    x.className = "topnav";
                }
            }
        </script>
        [% END %]
        [% END # / ( 'opac-main' ) %]

        [% IF ( opac-advsearch ) %]

        <div class="" style="margin: 0 auto;">
            <!-- style="background: url('http://iquc.org/wp-content/uploads/2019/01/iquc_logo.png') no-repeat;background-position: center;background-size: auto 100%;" -->
            <img src="/opac-tmpl/bootstrap/images/logo_iquc.png" alt="" class="col-12 p-0" style="width: auto;cursor: pointer;" onclick="location.href = '/'" >
            <center style="color: #005790;">مشروع اتحاد المكتبات العراقية</center>
        </div>
        [% END %]
        <!-- <div id="header-region" class="noprint row"> -->
        <!-- <div id="header-region" class="noprint row"
        style="background: url('/opac-tmpl/bootstrap/images/center-header-image.png') center,url('/opac-tmpl/bootstrap/images/left-header-image.png') no-repeat left ,url('/opac-tmpl/bootstrap/images/right-header-image.png') no-repeat right ;"> -->
        <!-- khakdaman -->

        [% IF ( OpacHeader ) %]
        <div class="container-fluid">
            <div class="row">
                <div class="col">
                    [% PROCESS koha_news_block news => OpacHeader %]
                </div>
            </div>
        </div>
        [% END %]

        [% IF ( OpacPublic ) %]
        [% IF ( bodyid != 'opac-main' ) %]
        <div class="container-fluid">
            [% UNLESS ( advsearch ) %]


            <div class="" style="display: flex;justify-content: space-between;">
                [% IF ( bodyid != 'opac-main' ) %]
                <style>
                    .small-size-responcive {
                        margin-top: 15px;
                        flex: 1;
                    }
                    @media screen and (max-width: 1450px) and (min-width: 1305px) {
                        #filter_search_top{
                            font-size: 0.98vw;
                        }
                    }
                    
                    @media screen and (max-width: 1305px) {
                        .small_flex_12{
                            flex: 0 0 100%;
                            max-width: 100%;
                        }
                        .size_1305_display_inherit{
                            display: inherit;
                        }
                    }
                    

                    @media screen and (max-width: 700px) {
                        .small_display_none {
                            /* flex: 0; */
                            display: none;
                        }
                        .small_display_inherit {
                            /* flex: 0; */
                            display: inherit;
                        }
                        .small_flex_100{
                            flex: 0 0 100% !important;
                        }
                        .small_margin_x_auto {
                            margin-left: auto !important;
                            margin-right: auto !important;
                        }
                    }
                    @media screen and (max-width: 1090px) {
                        .small-size-responcive {
                            /* flex: 0; */
                            display: none;
                        }
                    }
                </style>
                [% END %]
                    <div class="row small_display_inherit" style="margin-left: auto !important;margin-right: auto !important;">
                        <div style="margin: 0 auto; display: flex;" class="row">
                            <div class="col-5 small_flex_12" style="margin: auto 0;padding: 0px;">
                                <center>
                                    <img src="/opac-tmpl/bootstrap/images/logo_iquc.png" alt="" class="col-12 p-0" style="width: auto;cursor: pointer;" onclick="location.href = '/'">
                                </center>
                            </div>
                            <div id="opac-main-search" class="col-7 small_flex_12 small_margin_x_auto small_flex_100 size_1305_display_inherit" style="margin-left: initial;margin-right: initial;max-width: 100%;margin-top: auto;margin-bottom: auto;">
                                [% IF ( OpacCustomSearch ) %]
                                [% PROCESS koha_news_block news => OpacCustomSearch %]
                                [% ELSE %]

                                [% IF ( bodyid != 'opac-main' ) %]

                                <!-- khakdaman -->
                                <style>
                                    .idx_div2,
                                    .idx_div {
                                        background-color: #1b4984 !important;
                                    }

                                    .idx_div2 input[type="radio"]:checked+label {
                                        background-color: rgba(21, 122, 251, 0.5) !important;

                                    }
                                </style>
                                <form name="searchform" method="get" action="/cgi-bin/koha/opac-search.pl" id="searchform" style="margin: 0 auto;">

                                    <!-- khakdaman -->

                                    <div class="row">
                                        <div id="searchtitle" style="margin: 0px auto;">
                                            <!-- <img src="/opac-tmpl/bootstrap/images/unionsearch.png" style="max-width: 100%;"
                                                alt="جستجو در منابع کتابخانه های عراق" style="margin: 0px auto;display: block;"
                                                title="جستجو در منابع کتابخانه های عراق"> -->
                                        </div>
                                    </div>
                                    <!-- khakdaman -->


                                    <div class="col-sm-auto order-2 order-sm-2 idx_div" style='padding:0px;'
                                        id="filter_search_top">
                                        <input id="rad1" type="radio" name="idx" value="" checked="checked" />
                                        <label for="rad1">
                                            <span class="checkmark">

                                            </span>كافة الحقول</label>
                                        <input id="rad2" type="radio" name="idx" value="ti" />
                                        <label for="rad2">
                                            <span class="checkmark">

                                            </span> عنوان </label>
                                        <input id="rad3" type="radio" name="idx" value="au" />
                                        <label for="rad3">
                                            <span class="checkmark">

                                            </span> مؤلف </label>
                                        <input id="rad4" type="radio" name="idx" value="su" />
                                        <label for="rad4">
                                            <span class="checkmark">

                                            </span> موضوع </label>
                                        <!-- khakdman -->
                                        <!-- <input id="rad5" type="radio" name="idx" value="nb" /> -->
                                        <!-- <label for="rad5">
                            <span class="checkmark">

                            </span> تدمك </label>
                        <input id="rad6" type="radio" name="idx" value="ns" />
                        <label for="rad6">
                            <span class="checkmark">

                            </span> السلاسل </label>
                        <input id="rad7" type="radio" name="idx" value="callnum,phr" />
                        <label for="rad7">
                            <span class="checkmark">

                            </span> رقم الطلب </label> -->
                                        <!-- khakdman -->
                                    </div>
                                    <div class="form-row align-items-center" id="m">
                                        <div class="col-sm-auto order-1 order-sm-1" style="display:none;">
                                            <label for="masthead_search">[% UNLESS ( Koha.Preference(
                                                'OpacAddMastheadLibraryPulldown' ) == 1 )
                                                %] [% IF ( mylibraryfirst ) %] (في [% Branches.GetName( mylibraryfirst ) | html
                                                %] فقط) [% END
                                                %] [% END %]</label>
                                        </div>

                                        <div class="col-sm-auto order-2 order-sm-2" style="display:none">



                                            <select name="idx2" id="masthead_search" class="form-control">
                                                [% IF ( ms_kw ) %]
                                                <option selected="selected" value="">فهرس المكتبة</option>
                                                [% ELSE %]
                                                <option value="">فهرس المكتبة</option>
                                                [% END # /ms_kw %]
                                                [% IF ( ms_ti ) %]
                                                <option selected="selected" value="ti">عنوان</option>
                                                [% ELSE %]
                                                <option value="ti">عنوان</option>
                                                [% END # /ms_ti %]
                                                [% IF ( ms_au ) %]
                                                <option selected="selected" value="au">مؤلف</option>
                                                [% ELSE %]
                                                <option value="au">مؤلف</option>
                                                [% END # /ms_au%]
                                                [% IF ( ms_su ) %]
                                                <option selected="selected" value="su">الموضوع</option>
                                                [% ELSE %]
                                                <option value="su">الموضوع</option>
                                                [% END # /ms_su %]
                                                [% IF ( ms_nb ) %]
                                                <option selected="selected" value="nb">تدمك</option>
                                                [% ELSE %]
                                                <option value="nb">تدمك</option>
                                                [% END # /ms_nb%]
                                                [% IF ( ms_ns ) %]
                                                <option selected="selected" value="ns">تدمد</option>
                                                [% ELSE %]
                                                <option value="ns">تدمد</option>
                                                [% END # /ms_ns%]
                                                [% IF ( ms_se ) %]
                                                <option selected="selected" value="se">السلاسل</option>
                                                [% ELSE %]
                                                <option value="se">السلاسل</option>
                                                [% END # /ms_se %]
                                                [% IF ( Koha.Preference('OPACNumbersPreferPhrase') ) %]
                                                [% IF ( ms_callnumcommaphr ) %]
                                                <option selected="selected" value="callnum,phr">رقم الطلب</option>
                                                [% ELSE %]
                                                <option value="callnum,phr">رقم الطلب</option>
                                                [% END #/ms_callnumcommaphr %]
                                                [% ELSE %]
                                                [% IF ( ms_callnum ) %]
                                                <option selected="selected" value="callnum">رقم الطلب</option>
                                                [% ELSE %]
                                                <option value="callnum">رقم الطلب</option>
                                                [% END # /ms_callnum %]
                                                [% END # /IF OPACNumbersPreferPhrase %]
                                            </select>
                                        </div> <!-- /.col-sm-auto -->
                                        <style>
                                            /* khakdman */
                                            .transl2 {
                                                margin-bottom: 0px !important;
                                            }

                                            .div-transl2 {

                                                padding-left: 0px !important;
                                                padding-right: 0px !important;
                                                margin-bottom: 0px !important;
                                            }

                                            .div-transl2 select {
                                                margin-bottom: 0px !important;
                                            }

                                            .search-sm-filter {
                                                display: none;
                                            }

                                            @media screen and (max-width: 375px) {

                                                #m input,
                                                #m select {
                                                    font-size: 3.6vw;
                                                }
                                            }

                                            @media screen and (max-width: 773px) {

                                                .search-sm-filter {
                                                    display: inherit;
                                                }

                                                .search-sm-filter-libarary {
                                                    flex: 0 0 33.33%;
                                                    max-width: 33.33%;
                                                }

                                                .search-sm-filters {
                                                    -ms-flex: 0 0 100%;
                                                    flex: 0 0 100%;
                                                    max-width: 100%;
                                                    order: 2;
                                                }

                                                .search-sm-filters-order-5 {
                                                    -ms-flex: 0 0 100%;
                                                    flex: 0 0 100%;
                                                    max-width: 100%;
                                                    order: 5;
                                                }

                                            }

                                            /* khakdman */
                                        </style>
                                        <div class="col order-4 order-sm-3 div-transl2">
                                            [% IF ( ms_value ) %]
                                            <input class="col-12 transl1 transl2 form-control" id="translControl1" name="q"
                                                placeholder="ادخل عبارة البحث هنا" title="ادخل عبارة البحث هنا" type="text"
                                                autocomplete="off" value="[% ms_value | html %]" />
                                            <span id="translControl">

                                            </span>
                                            [% ELSE %]
                                            <input class="col-12 transl1 transl2 form-control" id="translControl1" name="q"
                                                autocomplete="off" placeholder="ادخل عبارة البحث هنا"
                                                title="ادخل عبارة البحث هنا" type="text" />
                                            <span id="translControl">

                                            </span>
                                            [% END # /ms_value %]
                                            <script>
                                                function auto_complit_responcive(x) {
                                                    console.log(x);
                                                    if (x.matches) {
                                                    document.getElementById('translControl1').setAttribute('autocomplete','off')
                                                    }else{
                                                    document.getElementById('translControl1').setAttribute('autocomplete','on')
                                                    }
                                                }
                        
                                                var x = window.matchMedia("(max-width: 900px)")
                                                auto_complit_responcive(x) // Call listener function at run time
                                                x.addListener(auto_complit_responcive) // Attach listener function on state changes 
                                            </script>
                                        </div> <!-- /.col -->

                                        [% IF ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
                                        <div
                                            class="col-sm-3 col-md-3 col-lg-2 order-3 order-sm-4 div-transl2 search-sm-filters">
                                            <div class="row">
                                                <!-- khakdaman -->

                                                <select name="branch_group_limit" id="select_library"
                                                    class="form-control col-12  search-sm-filter-libarary">
                                                    <option value="">كل المكتبات</option>

                                                    [% IF LibrarySearchGroups %]<optgroup label="المكتبات">[% END %]

                                                        [% FOREACH library IN Branches.all( selected => opac_name ) %]
                                                        [% IF library.selected %]
                                                        <option selected="selected"
                                                            value="branch:[% library.branchcode | html %]">[%
                                                            library.branchname | html %]</option>
                                                        [% ELSE %]
                                                        <option value="branch:[% library.branchcode | html %]">[%
                                                            library.branchname | html %]
                                                        </option>
                                                        [% END %]
                                                        [% END %]

                                                        [% IF LibrarySearchGroups %]
                                                    </optgroup>
                                                    <optgroup label="مجموعات">
                                                        [% FOREACH lsg IN LibrarySearchGroups %]
                                                        [% IF lsg.id == opac_name %]
                                                        <option selected="selected"
                                                            value="multibranchlimit-[% lsg.id | html %]">[% lsg.title |
                                                            html
                                                            %]</option>
                                                        [% ELSE %]
                                                        <option value="multibranchlimit-[% lsg.id | html %]">[% lsg.title | html
                                                            %]</option>
                                                        [% END # / bc.selected %]
                                                        [% END %]
                                                    </optgroup>
                                                    [% END # / BranchCategoriesLoop %]
                                                </select> <!-- /#select_library -->

                                                <select name="idx2" class="form-control col search-sm-filter">
                                                    [% IF ( ms_kw ) %]
                                                    <option selected="selected" value="">فهرس المكتبة</option>
                                                    [% ELSE %]
                                                    <option value="">فهرس المكتبة</option>
                                                    [% END # /ms_kw %]
                                                    [% IF ( ms_ti ) %]
                                                    <option selected="selected" value="ti">عنوان</option>
                                                    [% ELSE %]
                                                    <option value="ti">عنوان</option>
                                                    [% END # /ms_ti %]
                                                    [% IF ( ms_au ) %]
                                                    <option selected="selected" value="au">مؤلف</option>
                                                    [% ELSE %]
                                                    <option value="au">مؤلف</option>
                                                    [% END # /ms_au%]
                                                    [% IF ( ms_su ) %]
                                                    <option selected="selected" value="su">الموضوع</option>
                                                    [% ELSE %]
                                                    <option value="su">الموضوع</option>
                                                    [% END # /ms_su %]
                                                    [% IF ( ms_nb ) %]
                                                    <option selected="selected" value="nb">تدمك</option>
                                                    [% ELSE %]
                                                    <option value="nb">تدمك</option>
                                                    [% END # /ms_nb%]
                                                    [% IF ( ms_ns ) %]
                                                    <option selected="selected" value="ns">تدمد</option>
                                                    [% ELSE %]
                                                    <option value="ns">تدمد</option>
                                                    [% END # /ms_ns%]
                                                    [% IF ( ms_se ) %]
                                                    <option selected="selected" value="se">السلاسل</option>
                                                    [% ELSE %]
                                                    <option value="se">السلاسل</option>
                                                    [% END # /ms_se %]
                                                    [% IF ( Koha.Preference('OPACNumbersPreferPhrase') ) %]
                                                    [% IF ( ms_callnumcommaphr ) %]
                                                    <option selected="selected" value="callnum,phr">رقم الطلب</option>
                                                    [% ELSE %]
                                                    <option value="callnum,phr">رقم الطلب</option>
                                                    [% END #/ms_callnumcommaphr %]
                                                    [% ELSE %]
                                                    [% IF ( ms_callnum ) %]
                                                    <option selected="selected" value="callnum">رقم الطلب</option>
                                                    [% ELSE %]
                                                    <option value="callnum">رقم الطلب</option>
                                                    [% END # /ms_callnum %]
                                                    [% END # /IF OPACNumbersPreferPhrase %]
                                                </select>
                                                <select name="limit" class="form-control col search-sm-filter">

                                                    <option selected
                                                value=""
                                                >
                                                بحث عام
                                                </option>
                                                [% FOREACH itemtypeloo IN ItemTypes.Get %]
                                                <option 
                                                value="[% itemtypeloo.itemtype | html %]"
                                                >
                                                [% itemtypeloo.description | html %]
                                                </option>
                                                [% END %]
                                                </select>
                                                <!-- /khakdaman -->
                                            </div>
                                        </div> <!-- /.col-sm-auto -->




                                        <!-- khakdaman -->
                                        <div class="col-sm-auto  search-sm-filters-order-5 order-5"
                                            style="padding-left: 0px;padding-right: 0px;">
                                            <button type="submit" id="searchsubmit" class="btn btn-warning col-12 ">
                                                <i aria-hidden="true" class="fa fa-search text-white">

                                                </i>
                                            </button>
                                        </div>
                                        [% ELSE %]
                                        [% IF ( opac_limit_override ) %]
                                        [% IF ( opac_search_limit ) %]
                                        [% IF ( multibranchlimit = opac_search_limit.match( 'branch:(multibranchlimit-\d+)' ) )
                                        %]
                                        <input name="branch_group_limit" value="[% multibranchlimit.0 | html %]"
                                            type="hidden" />
                                        [% ELSE %]
                                        <input name="limit" value="[% opac_search_limit | html %]" type="hidden" />
                                        [% END %]
                                        [% END %]
                                        [% ELSE %]
                                        [% IF ( mylibraryfirst ) %]
                                        <input name="limit" value="branch:[% mylibraryfirst | html %]" type="hidden" />
                                        [% END %]
                                        [% END # / opac_limit_override %]
                                        <div class="order-5 col-sm-auto">
                                            <button type="submit" id="searchsubmit" class="btn btn-primary">اذهب</button>
                                        </div>
                                        [% END # / OpacAddMastheadLibraryPulldown %]
                                    </div> <!-- /.form-row -->
                                    <input type="hidden" name="weight_search" value="1">



                                    <!-- /khakdaman -->








                                    <div class="col-sm-auto order-2 order-sm-2 idx_div idx_div2 " style='padding:0px;'
                                        id="filter_search_bottom">
                                        <input id="ccc" type="radio" name="limit" value="" checked="checked" />
                                        <label for="ccc">بحث عام</label>
                                        
                                        [% FOREACH itemtypeloo IN ItemTypes.Get %]
                                        <input 
                                        id="[% itemtypeloo.itemtype | html %]"
                                        type="radio"
                                        name="limit"
                                        value="[% itemtypeloo.itemtype | html %]"
                                        />
                                        <label for="[% itemtypeloo.itemtype | html %]">[% itemtypeloo.description | html %]</label>
                                        [% END %]

                                    </div>




                                </form>
                                <!-- 
                                <form name="searchform" method="get" action="/cgi-bin/koha/opac-search.pl" id="searchform">



                                    <div class="col-sm-auto order-2 order-sm-2 idx_div" style='padding:0px;'>
                                        <input id="rad1" type="radio" name="idx" value="" checked="checked" /><label
                                            for="rad1"><span class="checkmark"></span> فهرس المكتبة</label>
                                        <input id="rad2" type="radio" name="idx" value="ti" /><label for="rad2"><span
                                                class="checkmark"></span> عنوان </label>
                                        <input id="rad3" type="radio" name="idx" value="au" /><label for="rad3"><span
                                                class="checkmark"></span> مؤلف </label>
                                        <input id="rad4" type="radio" name="idx" value="su" /><label for="rad4"><span
                                                class="checkmark"></span> الموضوع </label>
                                        <input id="rad5" type="radio" name="idx" value="nb" /><label for="rad5"><span
                                                class="checkmark"></span> تدمك </label>
                                        <input id="rad6" type="radio" name="idx" value="ns" /><label for="rad6"><span
                                                class="checkmark"></span> السلاسل </label>
                                        <input id="rad7" type="radio" name="idx" value="callnum,phr" /><label for="rad7"><span
                                                class="checkmark"></span> رقم الطلب </label>
                                    </div>
                                    <div class="form-row align-items-center" id="m">
                                        <div class="col-sm-auto order-1 order-sm-1" style="display:none;">
                                            <label for="masthead_search">[% UNLESS ( Koha.Preference(
                                                'OpacAddMastheadLibraryPulldown' ) == 1 ) %] [% IF ( mylibraryfirst ) %] (في [%
                                                Branches.GetName( mylibraryfirst ) | html %] فقط) [% END %] [% END %]</label>
                                        </div>

                                        <div class="col-sm-auto order-2 order-sm-2" style="display:none">



                                            <select name="idx2" id="masthead_search" class="form-control">
                                                [% IF ( ms_kw ) %]
                                                <option selected="selected" value="">فهرس المكتبة</option>
                                                [% ELSE %]
                                                <option value="">فهرس المكتبة</option>
                                                [% END # /ms_kw %]
                                                [% IF ( ms_ti ) %]
                                                <option selected="selected" value="ti">عنوان</option>
                                                [% ELSE %]
                                                <option value="ti">عنوان</option>
                                                [% END # /ms_ti %]
                                                [% IF ( ms_au ) %]
                                                <option selected="selected" value="au">مؤلف</option>
                                                [% ELSE %]
                                                <option value="au">مؤلف</option>
                                                [% END # /ms_au%]
                                                [% IF ( ms_su ) %]
                                                <option selected="selected" value="su">الموضوع</option>
                                                [% ELSE %]
                                                <option value="su">الموضوع</option>
                                                [% END # /ms_su %]
                                                [% IF ( ms_nb ) %]
                                                <option selected="selected" value="nb">تدمك</option>
                                                [% ELSE %]
                                                <option value="nb">تدمك</option>
                                                [% END # /ms_nb%]
                                                [% IF ( ms_ns ) %]
                                                <option selected="selected" value="ns">تدمد</option>
                                                [% ELSE %]
                                                <option value="ns">تدمد</option>
                                                [% END # /ms_ns%]
                                                [% IF ( ms_se ) %]
                                                <option selected="selected" value="se">السلاسل</option>
                                                [% ELSE %]
                                                <option value="se">السلاسل</option>
                                                [% END # /ms_se %]
                                                [% IF ( Koha.Preference('OPACNumbersPreferPhrase') ) %]
                                                [% IF ( ms_callnumcommaphr ) %]
                                                <option selected="selected" value="callnum,phr">رقم الطلب</option>
                                                [% ELSE %]
                                                <option value="callnum,phr">رقم الطلب</option>
                                                [% END #/ms_callnumcommaphr %]
                                                [% ELSE %]
                                                [% IF ( ms_callnum ) %]
                                                <option selected="selected" value="callnum">رقم الطلب</option>
                                                [% ELSE %]
                                                <option value="callnum">رقم الطلب</option>
                                                [% END # /ms_callnum %]
                                                [% END # /IF OPACNumbersPreferPhrase %]
                                            </select>
                                        </div>

                                        <div class="col order-4 order-sm-3">
                                            [% IF ( ms_value ) %]
                                            <input class="transl1 form-control" id="translControl1" name="q"
                                                title="ادخل مصطلح البحث" placeholder="ادخل مصطلح البحث" type="text"
                                                value="[% ms_value | html %]" /><span id="translControl"></span>
                                            [% ELSE %]
                                            <input class="transl1 form-control" id="translControl1" name="q"
                                                title="ادخل مصطلح البحث" placeholder="ادخل مصطلح البحث" type="text" /><span
                                                id="translControl"></span>
                                            [% END # /ms_value %]
                                        </div>

                                        [% IF ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
                                        <div class="col-sm col-md-3 col-lg-2 order-3 order-sm-4">
                                            <select name="branch_group_limit" id="select_library" class="form-control">
                                                <option value="">كل المكتبات</option>

                                                [% IF LibrarySearchGroups %]<optgroup label="المكتبات">[% END %]

                                                    [% FOREACH library IN Branches.all( selected => opac_name ) %]
                                                    [% IF library.selected %]
                                                    <option selected="selected" value="branch:[% library.branchcode | html %]">
                                                        [% library.branchname | html %]</option>
                                                    [% ELSE %]
                                                    <option value="branch:[% library.branchcode | html %]">[% library.branchname
                                                        | html %]</option>
                                                    [% END %]
                                                    [% END %]

                                                    [% IF LibrarySearchGroups %]
                                                </optgroup>
                                                <optgroup label="مجموعات">
                                                    [% FOREACH lsg IN LibrarySearchGroups %]
                                                    [% IF lsg.id == opac_name %]
                                                    <option selected="selected" value="multibranchlimit-[% lsg.id | html %]">[%
                                                        lsg.title | html %]</option>
                                                    [% ELSE %]
                                                    <option value="multibranchlimit-[% lsg.id | html %]">[% lsg.title | html %]
                                                    </option>
                                                    [% END # / bc.selected %]
                                                    [% END %]
                                                </optgroup>
                                                [% END # / BranchCategoriesLoop %]
                                            </select> 
                                        </div> 




                                        <div class="col-sm-auto order-5">
                                            <button type="submit" id="searchsubmit" class="btn btn-primary"><i
                                                    aria-hidden="true" class="fa fa-search"></i></button>
                                        </div>
                                        [% ELSE %]
                                        [% IF ( opac_limit_override ) %]
                                        [% IF ( opac_search_limit ) %]
                                        [% IF ( multibranchlimit = opac_search_limit.match( 'branch:(multibranchlimit-\d+)' ) )
                                        %]
                                        <input name="branch_group_limit" value="[% multibranchlimit.0 | html %]"
                                            type="hidden" />
                                        [% ELSE %]
                                        <input name="limit" value="[% opac_search_limit | html %]" type="hidden" />
                                        [% END %]
                                        [% END %]
                                        [% ELSE %]
                                        [% IF ( mylibraryfirst ) %]
                                        <input name="limit" value="branch:[% mylibraryfirst | html %]" type="hidden" />
                                        [% END %]
                                        [% END # / opac_limit_override %]
                                        <div class="order-5 col-sm-auto">
                                            <button type="submit" id="searchsubmit" class="btn btn-primary">اذهب</button>
                                        </div>
                                        [% END # / OpacAddMastheadLibraryPulldown %]
                                    </div>
                                    <input type="hidden" name="weight_search" value="1">











                                    <div class="col-sm-auto order-2 order-sm-2 idx_div idx_div2" style='padding:0px;'>
                                        <input id="ccc" type="radio" name="itype" value="" checked="checked" /><label for="ccc">
                                            كل المواد</label>
                                        [% FOREACH itemtypeloo IN ItemTypes.Get %]
                                        <input id="rad[% itemtypeloo.description %]" type="radio" name="itype"
                                            value="ti" /><label for="rad[% itemtypeloo.description %]"> [%
                                            itemtypeloo.description %] </label>
                                        [% END %]

                                    </div>




                                </form> -->
                                <!-- khakdaman -->
                                <style>
                                    #opac-main-search {
                                        max-width: 800px;
                                        padding: 5px;
                                        padding-top: 0px;
                                        margin: 0px auto;
                                        background: none;
                                    }

                                    .navbar-nav>li>a,
                                    .navbar-nav .fa.fa-icon-black {
                                        color: #fff;
                                    }
                                </style>
                                <!-- <form name="searchform" method="get" action="/cgi-bin/koha/opac-search.pl" id="searchform">
        
        
        
        <div class="col-sm-auto order-2 order-sm-2 idx_div" style='padding:0px;'> 
        <input id="rad1" type="radio" name="idx" value="" checked="checked"/><label for="rad1"><span class="checkmark"></span> فهرس المكتبة</label>
        <input id="rad2" type="radio" name="idx" value="ti"/><label for="rad2"><span class="checkmark"></span> عنوان </label>
        <input id="rad3" type="radio" name="idx" value="au"/><label for="rad3"><span class="checkmark"></span> مؤلف </label>
        <input id="rad4" type="radio" name="idx" value="su"/><label for="rad4"><span class="checkmark"></span> الموضوع </label>
        <input id="rad5" type="radio" name="idx" value="nb"/><label for="rad5"><span class="checkmark"></span> تدمك </label>
        <input id="rad6" type="radio" name="idx" value="ns"/><label for="rad6"><span class="checkmark"></span> السلاسل </label>
        <input id="rad7" type="radio" name="idx" value="callnum,phr"/><label for="rad7"><span class="checkmark"></span> رقم الطلب </label>
        </div>
        <div class="form-row align-items-center" >
        <div class="col-sm-auto order-1 order-sm-1" style="display:none;">
        <label for="masthead_search">[% UNLESS ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %] [% IF ( mylibraryfirst ) %] (في [% Branches.GetName( mylibraryfirst ) | html %] فقط) [% END %] [% END %]</label>
        </div>

        <div class="col-sm-auto order-2 order-sm-2" style="display:none">



        <select name="idx2" id="masthead_search" class="form-control">
        [% IF ( ms_kw ) %]
        <option selected="selected" value="">فهرس المكتبة</option>
        [% ELSE %]
        <option value="">فهرس المكتبة</option>
        [% END # /ms_kw %]
        [% IF ( ms_ti ) %]
        <option selected="selected" value="ti">عنوان</option>
        [% ELSE %]
        <option value="ti">عنوان</option>
        [% END # /ms_ti %]
        [% IF ( ms_au ) %]
        <option selected="selected" value="au">مؤلف</option>
        [% ELSE %]
        <option value="au">مؤلف</option>
        [% END # /ms_au%]
        [% IF ( ms_su ) %]
        <option selected="selected" value="su">الموضوع</option>
        [% ELSE %]
        <option value="su">الموضوع</option>
        [% END # /ms_su %]
        [% IF ( ms_nb ) %]
        <option selected="selected" value="nb">تدمك</option>
        [% ELSE %]
        <option value="nb">تدمك</option>
        [% END # /ms_nb%]
        [% IF ( ms_ns ) %]
        <option selected="selected" value="ns">تدمد</option>
        [% ELSE %]
        <option value="ns">تدمد</option>
        [% END # /ms_ns%]
        [% IF ( ms_se ) %]
        <option selected="selected" value="se">السلاسل</option>
        [% ELSE %]
        <option value="se">السلاسل</option>
        [% END # /ms_se %]
        [% IF ( Koha.Preference('OPACNumbersPreferPhrase') ) %]
        [% IF ( ms_callnumcommaphr ) %]
        <option selected="selected" value="callnum,phr">رقم الطلب</option>
        [% ELSE %]
        <option value="callnum,phr">رقم الطلب</option>
        [% END #/ms_callnumcommaphr %]
        [% ELSE %]
        [% IF ( ms_callnum ) %]
        <option selected="selected" value="callnum">رقم الطلب</option>
        [% ELSE %]
        <option value="callnum">رقم الطلب</option>
        [% END # /ms_callnum %]
        [% END # /IF OPACNumbersPreferPhrase %]
        </select>
        </div> 

        <div class="col order-4 order-sm-3">
        [% IF ( ms_value ) %]
        <input class="transl1 form-control" id="translControl1" name="q" title="ادخل مصطلح البحث" placeholder="ادخل مصطلح البحث" type="text" value="[% ms_value | html %]" /><span id="translControl"></span>
        [% ELSE %]
        <input class="transl1 form-control" id="translControl1" name="q" title="ادخل مصطلح البحث" placeholder="ادخل مصطلح البحث" type="text" /><span id="translControl"></span>
        [% END # /ms_value %]
        </div> 

        [% IF ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 ) %]
        <div class="col-sm col-md-3 col-lg-2 order-3 order-sm-4">
        <select name="branch_group_limit" id="select_library" class="form-control">
        <option value="">كل المكتبات</option>

        [% IF LibrarySearchGroups %]<optgroup label="المكتبات">[% END %]

        [% FOREACH library IN Branches.all( selected => opac_name ) %]
        [% IF library.selected %]
        <option selected="selected" value="branch:[% library.branchcode | html %]">[% library.branchname | html %]</option>
        [% ELSE %]
        <option value="branch:[% library.branchcode | html %]">[% library.branchname | html %]</option>
        [% END %]
        [% END %]

        [% IF LibrarySearchGroups %]
        </optgroup>
        <optgroup label="مجموعات">
        [% FOREACH lsg IN LibrarySearchGroups %]
        [% IF lsg.id == opac_name %]
        <option selected="selected" value="multibranchlimit-[% lsg.id | html %]">[% lsg.title | html %]</option>
        [% ELSE %]
        <option value="multibranchlimit-[% lsg.id | html %]">[% lsg.title | html %]</option>
        [% END # / bc.selected %]
        [% END %]
        </optgroup>
        [% END # / BranchCategoriesLoop %]
        </select> 
        </div>
        
        
        
        <div class="col-sm col-md-3 col-lg-2 order-3 order-sm-4">
        <select class="form-control" name='itype'>
        [% FOREACH itemtypeloo IN ItemTypes.Get %] 
        <option >[% itemtypeloo.description %] </option>
        [% END %]
        </select>

        
        </div>
        <div class="col-sm-auto order-5">
        <button type="submit" id="searchsubmit" class="btn btn-primary">اذهب</button>
        </div>
        [% ELSE %]
        [% IF ( opac_limit_override ) %]
        [% IF ( opac_search_limit ) %]
        [% IF ( multibranchlimit = opac_search_limit.match( 'branch:(multibranchlimit-\d+)' ) ) %]
        <input name="branch_group_limit" value="[% multibranchlimit.0 | html %]" type="hidden" />
        [% ELSE %]
        <input name="limit" value="[% opac_search_limit | html %]" type="hidden" />
        [% END %]
        [% END %]
        [% ELSE %]
        [% IF ( mylibraryfirst ) %]
        <input name="limit" value="branch:[% mylibraryfirst | html %]" type="hidden" />
        [% END %]
        [% END # / opac_limit_override %]
        <div class="order-5 col-sm-auto">
        <button type="submit" id="searchsubmit" class="btn btn-primary">اذهب</button>
        </div>
        [% END # / OpacAddMastheadLibraryPulldown %]
        </div>
        <input type="hidden" name="weight_search" value="1">
        </form> -->



                                [% END # / ( 'opac-main' ) %]
                                [% END # / ( OpacCustomSearch ) %]
                            </div><!-- /#opac-main-search -->
                        </div>
                    </div>
            </div> <!-- /.row -->
            [% END # / UNLESS advsearch %]


        </div> <!-- /.container-fluid -->
        [% END # / ( 'opac-main' ) %]
        [% END # / OpacPublic %]
        <!-- khakdaman -->
        [% IF ( bodyid == 'opac-main' ) %]
        <style>
            @media screen and (max-width: 600px) {
                .header-image-right-and-left {
                    display: none;
                }

                .header-image-center {
                    flex: 0 0 100%;
                    max-width: 100%;
                }
            }
        </style>
        <div class="container-fluid row">
            <!-- <div class="col-4"> -->
            <div class="col-1 header-image-right-and-left">
            </div>
            <div class="col-10 p-0 header-image-center align-self-center text-center       ">
                <!-- style="background: url('http://iquc.org/wp-content/uploads/2019/01/iquc_logo.png') no-repeat;background-position: center;background-size: auto 100%;" -->
                <img src="/opac-tmpl/bootstrap/images/logo_iquc.png" alt="" class="col-12 p-0" style="width: auto;cursor: pointer;" onclick="location.href = '/'">
                <center style="color: #005790;">مشروع اتحاد المكتبات العراقية</center>
            </div>
            <div class="col-1 header-image-right-and-left">

                <!-- <div class="col-8"> -->
                <nav class="navbar navbar-expand" style="justify-content: left;direction: ltr;">

                    <div class="dropdown">
                        <span
                            class="fa fa-list fa-icon-black font-medium-3 dropdown-toggle nav-hide-arrow cursor-pointer"
                            data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" role="menu">
                        </span>
                        <div class="dropdown-menu" style="right: inherit;direction: rtl; padding: 0 0 !important;">

                            [% IF ( Koha.Preference( 'opacuserlogin' ) == 1 ) %]
                            [% IF ( loggedinusername ) %]
                            <a href="#" class="nav-link p-1 login-link" id="user-menu" data-toggle="dropdown"
                                role="button">
                                <i class="fa fa-user fa-icon-black fa-fw" aria-hidden="true"></i>
                                [% INCLUDE 'patron-title.inc' patron = logged_in_user no_html = 1 %]
                            </a>
                            [% ELSE %]
                            [% IF Koha.Preference('casAuthentication') %]
                            [%# CAS authentication is too complicated for modal window %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl"><i
                                    class="fa fa-user fa-icon-black fa-fw" aria-hidden="true"></i>تسجيل الدخول إلى
                                حسابك</a>
                            [% ELSIF ( Koha.Preference('GoogleOpenIDConnect') == 1 ) %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/svc/auth/googleopenidconnect"
                                role="button" data-toggle="modal"><i class="fa fa-user fa-icon-black fa-fw"
                                    aria-hidden="true"></i>تسجيل
                                الدخول إلى حسابك
                            </a>
                            [% ELSE %]
                            <a href="/cgi-bin/koha/opac-user.pl" class="nav-link p-1 login-link loginModal-trigger"><i
                                    class="fa fa-user fa-icon-black fa-fw" aria-hidden="true"></i>تسجيل
                                الدخول إلى حسابك</a>
                            [% END %]
                            [% END %]
                            [% END %]
                            [% IF ( Koha.Preference( 'opacbookbag' ) == 1 ) %]
                            <a class="nav-link p-1" href="#" id="cartmenulink" role="button"
                                title="تجميع المواد التي تهمك">
                                <i id="carticon" class="fa fa-shopping-cart fa-icon-black" aria-hidden="true"></i>
                                سلة
                                <span id="basketcount"></span>
                            </a>
                            [% END %]
                            [% IF checkouts && checkouts > 0 %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl#opac-user-checkouts">
                                <span class="user_checkouts_count count_label">[% checkouts | html %]</span>
                                [% tn('checkout', 'checkouts', checkouts ) | html %]
                            </a>
                            [% END %]




                            [% IF overdues && overdues > 0 %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl#opac-user-overdues">
                                <span class="user_overdues_count count_label">[% overdues | html %]</span>
                                [% tn('overdue', 'overdues', overdues ) | html %]
                            </a>
                            [% END %]
                            [% IF holds_pending && holds_pending > 0 %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl#opac-user-holds">
                                <span class="user_holds_pending_count count_label">[% holds_pending | html
                                    %]</span>
                                [% tn('hold pending', 'holds pending', holds_pending ) | html %]
                            </a>
                            [% END %]
                            [% IF holds_waiting && holds_waiting > 0 %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl#opac-user-holds">
                                <span class="user_holds_waiting_count count_label">[% holds_waiting | html
                                    %]</span>
                                [% tn('hold waiting', 'holds waiting', holds_waiting ) | html %]
                            </a>
                            [% END %]
                            [% IF total_owing && total_owing > 0 %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-account.pl">
                                <span class="user_fines_count count_label">[% total_owing | $Price with_symbol
                                    => 1 %]</span>
                                due in fines and charges
                            </a>
                            [% END %]
                            [% IF patron_messages && patron_messages.count > 0 || opacnote %]
                            [% IF opacnote %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl">
                                <span class="count_label">[% patron_messages.count + 1 | html %]</span>
                                [% tn('message', 'messages', patron_messages.count + 1 ) | html %]
                            </a>
                            [% ELSE %]
                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-user.pl">
                                <span class="count_label">[% patron_messages.count | html %]</span>
                                [% tn('message', 'messages', patron_messages.count ) | html %]
                            </a>
                            [% END %]
                            [% END %]


                            <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-search-history.pl"
                                title="عرض سجل بحثك">سِجل
                                البحث</a>
                            <a class="nav-link p-1 logout clearsh"
                                href="/cgi-bin/koha/opac-search-history.pl?action=delete" title="حذف سِجل بحثك"><i
                                    class="fa fa-trash" aria-hidden="true"></i> مسح</a>
                            [% IF (loggedinusername ) %]
                            <a class="nav-link p-1 logout logouting_khakdaman"
                                href="/cgi-bin/koha/opac-main.pl?logout.x=1" title="logout">
                                <i class="fa fa-outdent" aria-hidden="true"></i> logout</a>
                            <script>

                                // khakdaman
                                document.addEventListener("DOMContentLoaded", function (event) {
                                    MSG_LOGOUTING_ACOUNT = 'Are you sure?'
                                    $(".logouting_khakdaman").on("click", function () {
                                        return confirmDelete(MSG_LOGOUTING_ACOUNT);
                                    });
                                });
                                // khakdaman

                            </script>
                            [% END %]

                            [% IF ( !Koha.Preference( 'opacuserlogin') || !loggedinusername ) %]
                            [% IF Koha.Preference( 'EnableOpacSearchHistory' ) %]
                            <!-- <a class="nav-link p-1 login-link" href="/cgi-bin/koha/opac-search-history.pl"
                                title="عرض سجل بحثك">سِجل
                                البحث</a>
                            <a class="nav-link p-1 logout clearsh"
                                href="/cgi-bin/koha/opac-search-history.pl?action=delete" title="حذف سِجل بحثك"><i
                                    class="fa fa-trash" aria-hidden="true"></i> مسح</a> -->
                            [% END %]
                            [% END %]
                        </div>
                    </div>

                </nav> <!-- /navbar -->

                <!-- Login form hidden by default, used for modal window -->
                <div id="loginModal" class="modal" tabindex="-1" role="dialog" aria-labelledby="modalLoginLabel"
                    aria-hidden="true">
                    <div class="modal-dialog">
                        <div class="modal-content">
                            <div class="modal-header">
                                <h2 class="modal-title" id="modalLoginLabel">تسجيل الدخول إلى حسابك</h2>
                                <button aria-label="إغلاق" class="closebtn" data-dismiss="modal" type="button">
                                    <span aria-hidden="true">&times;</span>
                                </button>
                            </div>
                            <form action="/cgi-bin/koha/opac-user.pl" method="post" name="auth" id="modalAuth">
                                <input type="hidden" name="has-search-query" id="has-search-query" value="" />
                                <div class="modal-body">
                                    [% IF ( shibbolethAuthentication ) %]
                                    [% IF ( invalidShibLogin ) %]
                                    <!-- This is what is displayed if shibboleth login has failed to match a koha user -->
                                    <div class="alert alert-info">
                                        <p>عذرا، هوية Shibboleth الخاصة بك لا تطابق هوية مكتبة صحيحة. إذا كان لديك تسجيل
                                            دخول
                                            محلي، يمكنك استخدامه أدناه.</p>
                                    </div>
                                    [% ELSE %]
                                    <h3>تسجيل دخول Shibboleth </h3>
                                    <p><a href="[% shibbolethLoginUrl | $raw %]">Log in using a Shibboleth account</a>.
                                    </p>
                                    [% UNLESS Koha.Preference('opacShibOnly') %]
                                    <h3>تسجيل دخول محلِّي</h3>
                                    [% END %]
                                    [% END %]
                                    [% END %]
                                    [% UNLESS Koha.Preference('opacShibOnly') %]
                                    <input type="hidden" name="koha_login_context" value="opac" />
                                    <fieldset class="brief">
                                        <label for="muserid">تسجيل الدخول:</label><input type="text" id="muserid"
                                            name="userid" />
                                        <label for="mpassword">كلمة المرور:</label><input type="password" id="mpassword"
                                            name="password" />
                                        [% IF ( OpacLoginInstructions ) %]
                                        <div id="nologininstructions-modal" class="nologininstructions">
                                            [% PROCESS koha_news_block news => OpacLoginInstructions %]
                                        </div>
                                        [% END %]
                                        [% IF Koha.Preference('OpacPasswordChange') && Categories.can_any_reset_password
                                        %]
                                        <div id="forgotpassword-modal" class="forgotpassword">
                                            <a href="/cgi-bin/koha/opac-password-recovery.pl">نسيت كلمة مرورك؟</a>
                                        </div>
                                        [% END %]
                                        [% IF PatronSelfRegistration && PatronSelfRegistrationDefaultCategory %]
                                        <div id="patronregistration-modal" class="patronregistration">
                                            <p>أليس لديك حساب ؟ <a href="/cgi-bin/koha/opac-memberentry.pl">سجل من
                                                    هنا.</a>
                                            </p>
                                        </div>
                                        [% END %]
                                    </fieldset>
                                    [% END %]
                                </div>
                                [% UNLESS Koha.Preference('opacShibOnly') %]
                                <div class="modal-footer">
                                    <input class="btn btn-primary" type="submit" value="تسجيل الدخول" />
                                </div>
                                [% END %]
                            </form> <!-- /#auth -->
                        </div> <!-- /.modal-content -->
                    </div> <!-- /.modal-dialog -->
                </div> <!-- /#modalAuth -->
            </div>
        </div>
        [% END # / ( 'opac-main' ) %]

        <!-- khakdaman -->
    </div> <!-- / header-region -->