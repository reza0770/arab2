[% IF patron_messages.count OR opacnote %]
 <div class="alert alert-info">
 <h3>رسائل من أجلك</h3>
 <ul>
 [% FOREACH message IN patron_messages %]
 <li>
 <strong>[% message.message | html | html_line_break %]</strong><br>
 &nbsp;&nbsp;&nbsp;<em>مكتوب في [% message.message_date | $KohaDates %] بواسطة [% Branches.GetName(message.branchcode) | html %]</em>
 </li>
 [% END %]

 [% IF ( opacnote ) %]<li>[% opacnote | html | html_line_break %]</li>[% END %]
 </ul>
 </div>
[% END %]
