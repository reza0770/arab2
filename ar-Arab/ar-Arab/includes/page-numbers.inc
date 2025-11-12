[% USE raw %]
[% IF ( PAGE_NUMBERS ) %]
<!-- <link rel="stylesheet" href="https://cdn.rtlcss.com/bootstrap/v4.5.3/css/bootstrap.min.css" integrity="sha384-JvExCACAZcHNJEc7156QaHXTnQL3hQBixvj5RV5buE7vgnNEzzskDtx9NQ4p6BJe" crossorigin="anonymous"> -->
<!-- <div class="row d-none text-center  " id="select_pagination" >
            
    [% IF ( previous_page_offset.defined ) %]
    <div class="col-3 mx-1 my-1 p-0" >
        <a aria-label="اذهب إلى الصفحة الأولى" class=" btn btn-default p-0 form-control " style="height: auto;"
            href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]"><i
                class="fa fa-fw fa-angle-double-right" aria-hidden="true"></i> أولا</a>
    </div>
    <div class="col-3 mx-1 my-1 p-0" >
        <a aria-label="اذهب إلى الصفحة السابقة" class=" btn btn-default p-0 form-control " style="height: auto;"
            href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% previous_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
            <i class="fa fa-fw fa-angle-right" aria-hidden="true"></i> السابق</a>
    </div>
    [% END %]
        
    [% FOREACH PAGE_NUMBER IN PAGE_NUMBERS %]
    [% IF ( PAGE_NUMBER.highlight ) %]
        
    <div class="col-1 mx-1 my-1 p-0" >
                
        <a class=" btn btn-default p-0 form-control disabled" style="height: auto;" aria-label="اذهب إلى صفحة [% PAGE_NUMBER.pg | html %]" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% PAGE_NUMBER.offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
            [% PAGE_NUMBER.pg | html %]
        </a>
    </div>
    [% ELSE %]
    
    <div class="col-1 mx-1 my-1 p-0" >
                
        <a class=" btn btn-default p-0 form-control" style="height: auto;" aria-label="اذهب إلى صفحة [% PAGE_NUMBER.pg | html %]" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% PAGE_NUMBER.offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
            [% PAGE_NUMBER.pg | html %]
        </a>
    </div>
    [% END %]
    [% END %]
    
    [% IF ( next_page_offset ) %]
    <div class="col-3 mx-1 my-1 p-0" >
        <a aria-label="اذهب إلى الصفحة الرئيسية" class=" btn btn-default p-0 form-control " style="height: auto;"
            href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% next_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">التالي<i
                class="fa fa-fw fa-angle-left" aria-hidden="true"></i></a>
    </div>
    <div class="col-3 mx-1 my-1 p-0" >
        <a aria-label="اذهب إلى الصفحة الأخيرة" class=" btn btn-default p-0 form-control " style="height: auto;"
            href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% last_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">آخر<i
                class="fa fa-fw fa-angle-double-left" aria-hidden="true"></i></a>
    </div>
    [% END %]
</div> -->
<div class="nav_pages d-none px-0" id="select_pagination">
    <ul id="listResults">

        [% IF ( previous_page_offset.defined ) %]
        <li class="li_pag_1 mt-1">
            <a aria-label="اذهب إلى الصفحة الأولى" class="a_pag" style="background-color: #fff; color: #00588f;"
            href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]"><i
                class="fa fa-fw fa-angle-double-right" aria-hidden="true"></i> أولا</a>
        </li>
        <li class="li_pag_1 mt-1">
            <a aria-label="اذهب إلى الصفحة السابقة" class="a_pag" style="background-color: #fff; color: #00588f;"
                href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% previous_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
                <i class="fa fa-fw fa-angle-right" aria-hidden="true"></i> السابق</a>
        </li>
        [% END %]

        [% FOREACH PAGE_NUMBER IN PAGE_NUMBERS %]
        [% IF ( PAGE_NUMBER.highlight ) %]

        <li class="li_pag_1_active mt-1">

            <a class="a_pag disabled"  style="background-color: #007bff; color: #fff;pointer-events: none;" aria-label="اذهب إلى صفحة [% PAGE_NUMBER.pg | html %]"
                href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% PAGE_NUMBER.offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
                [% PAGE_NUMBER.pg | html %]
            </a>
        </li>
        [% ELSE %]

        <li class="li_pag_1 mt-1">

            <a class="a_pag" style="background-color: #fff; color: #00588f;" aria-label="اذهب إلى صفحة [% PAGE_NUMBER.pg | html %]"
                href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% PAGE_NUMBER.offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
                [% PAGE_NUMBER.pg | html %]
            </a>
        </li>
        [% END %]
        [% END %]

        [% IF ( next_page_offset ) %]

        <li class="li_pag_1 mt-1">
            <a aria-label="اذهب إلى الصفحة الرئيسية" class="a_pag" style="background-color: #fff; color: #00588f;"
                href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% next_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">التالي<i
                    class="fa fa-fw fa-angle-left" aria-hidden="true"></i></a>

        </li>
        <li class="li_pag_1 mt-1">
            <a aria-label="اذهب إلى الصفحة الأخيرة" class="a_pag" style="background-color: #fff; color: #00588f;"
                href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% last_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">آخر
                <i                     class="fa fa-fw fa-angle-double-left" aria-hidden="true"></i></a>
        </li>
        [% END %]

        <!-- <li class="li_pag_1 highlight">

            <a class="a_pag" href="opac-detail.pl?biblionumber=656758&amp;query_desc=" id="a_pag_1"
                title="عرض التسجيلة " ""="">1</a>
        </li>
 -->

    </ul> <!-- /#listResults -->
</div>
<nav aria-label="ترقيم صفحات نتائج البحث" class="pagination pagination-sm noprint" id="nav_paginaition"
    style="overflow-x: auto;">
    [% IF hits_to_paginate < total %] <h6>[% hits_to_paginate | html %] من [% total | html %] النتائج التي تم تحميلها،
        قم بتنقيح بحثك لعرض تسجيلات أخرى</h6>
        [% END %]

        <ul class="pagination" style="overflow: auto;">
            [% IF ( previous_page_offset.defined ) %]
            <li class="page-item">
                <a aria-label="اذهب إلى الصفحة الأولى" class="page-link"
                    href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]"><i
                        class="fa fa-fw fa-angle-double-right" aria-hidden="true"></i> أولا</a>
            </li>
            <li class="page-item">
                <a aria-label="اذهب إلى الصفحة السابقة" class="page-link"
                    href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% previous_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
                    <i class="fa fa-fw fa-angle-right" aria-hidden="true"></i> السابق</a>
            </li>
            [% END %]
            [% FOREACH PAGE_NUMBER IN PAGE_NUMBERS %]
            [% IF ( PAGE_NUMBER.highlight ) %]
            <li class="page-item active">
                <p aria-current="true" aria-disabled="true"
                    aria-label="الصفحة الحالية: صفحة [% PAGE_NUMBER.pg | html %]" class="page-link text-white">
                    [%PAGE_NUMBER.pg | html %]</p>
            </li>
            [% ELSE %]
            <li class="page-item">
                <a aria-label="اذهب إلى صفحة [% PAGE_NUMBER.pg | html %]" class="page-link"
                    href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% PAGE_NUMBER.offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">[%
                    PAGE_NUMBER.pg | html %]</a>
            </li>
            [% END %]
            [% END %]
            [% IF ( next_page_offset ) %]
            <li class="page-item">
                <a aria-label="اذهب إلى الصفحة الرئيسية" class="page-link"
                    href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% next_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">التالي<i
                        class="fa fa-fw fa-angle-left" aria-hidden="true"></i></a>
            </li>
            <li class="page-item">
                <a aria-label="اذهب إلى الصفحة الأخيرة" class="page-link"
                    href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% last_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">آخر<i
                        class="fa fa-fw fa-angle-double-left" aria-hidden="true"></i></a>
            </li>
            [% END %]
        </ul>
</nav>
<!-- / khakdaman -->
<style>
    @media screen and (max-width: 600px) {
        #nav_paginaition {
            display: none;
        }

        #select_pagination {
            display: flex !important;
        }
    }
    .li_pag_1{
        border: 1px rgb(222, 226, 230) solid;
    }
    .li_pag_1 a:hover{
        background-color: #e9ecef !important;
    }
</style>
[% END %]