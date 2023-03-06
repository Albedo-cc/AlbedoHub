#pragma once

#include <string>
/*
    [Comment Index]
    UserName
    Content
    Verification Code
    Tail
*/

namespace
{
    struct register_mail
    {
        static void set_name(const std::string& name)
        {
            if (name.size() > 40) throw std::runtime_error("Name is longer than 40 Bytes!");
            static const size_t pos_name = register_mail::content.rfind("[--------$First$Name$(40Bytes)$--------]");
            static std::string placeholder = "                                        "; // 40B blank
            placeholder.replace(0, name.size(), std::string(name));
            register_mail::content.replace(pos_name, 40, placeholder);
        }

        static void set_name(const std::u8string& name)
        {
            set_name(reinterpret_cast<const char*>(name.c_str()));
        }

        static void set_vcode(const std::string& verification_code)
        {
            if (verification_code.size() > 6) throw std::runtime_error("Verification Code is longer than 6 Bytes!");
            static const size_t pos_vcode = register_mail::content.rfind("$CODE$");
            static std::string placeholder = "      "; // 6B blank
            placeholder.replace(0, verification_code.size(), verification_code);
            register_mail::content.replace(pos_vcode, 6, placeholder);
        }
        static const std::string& get() { return register_mail::content; }

    private:
        static std::string content;
    };

    std::string register_mail::content =
        "<!DOCTYPE html>"
        "<html xmlns=\"http://www.w3.org/1999/xhtml\" xmlns:v=\"urn:schemas-microsoft-com:vml\" xmlns:o=\"urn:schemas-microsoft-com:office:office\">"
        ""
        "<head>"
        "<title>"
        "</title>"
        "<!--[if !mso]><!-->"
        "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
        "<!--<![endif]-->"
        "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
        "<style type=\"text/css\">"
        "#outlook a {"
        "padding: 0;"
        "}"
        ""
        "body {"
        "margin: 0;"
        "padding: 0;"
        "-webkit-text-size-adjust: 100%;"
        "-ms-text-size-adjust: 100%;"
        "}"
        ""
        "table,"
        "td {"
        "border-collapse: collapse;"
        "mso-table-lspace: 0pt;"
        "mso-table-rspace: 0pt;"
        "}"
        ""
        "img {"
        "border: 0;"
        "height: auto;"
        "line-height: 100%;"
        "outline: none;"
        "text-decoration: none;"
        "-ms-interpolation-mode: bicubic;"
        "}"
        ""
        "p {"
        "display: block;"
        "margin: 13px 0;"
        "}"
        ""
        "</style>"
        "<!--[if mso]>"
        "<noscript>"
        "<xml>"
        "<o:OfficeDocumentSettings>"
        "<o:AllowPNG/>"
        "<o:PixelsPerInch>96</o:PixelsPerInch>"
        "</o:OfficeDocumentSettings>"
        "</xml>"
        "</noscript>"
        "<![endif]-->"
        "<!--[if lte mso 11]>"
        "<style type=\"text/css\">"
        ".mj-outlook-group-fix { width:100% !important; }"
        "</style>"
        "<![endif]-->"
        "<!--[if !mso]><!-->"
        "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,500,700\" rel=\"stylesheet\" type=\"text/css\">"
        "<style type=\"text/css\">"
        "@import url(https://fonts.googleapis.com/css?family=Open+Sans:300,400,500,700);"
        ""
        "</style>"
        "<!--<![endif]-->"
        "<style type=\"text/css\">"
        "@media only screen and (min-width:480px) {"
        ".mj-column-per-100 {"
        "width: 100% !important;"
        "max-width: 100%;"
        "}"
        "}"
        ""
        "</style>"
        "<style media=\"screen and (min-width:480px)\">"
        ".moz-text-html .mj-column-per-100 {"
        "width: 100% !important;"
        "max-width: 100%;"
        "}"
        ""
        "</style>"
        "<style type=\"text/css\">"
        "@media only screen and (max-width:480px) {"
        "table.mj-full-width-mobile {"
        "width: 100% !important;"
        "}"
        ""
        "td.mj-full-width-mobile {"
        "width: auto !important;"
        "}"
        "}"
        ""
        "</style>"
        "<style type=\"text/css\">"
        "</style>"
        "</head>"
        ""
        "<body style=\"word-spacing:normal;background-color:#ffffff;\">"
        "<div style=\"background-color:#ffffff;\">"
        "<!--[if mso | IE]><table align=\"center\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"\" role=\"presentation\" style=\"width:600px;\" width=\"600\" bgcolor=\"#ffffff\" ><tr><td style=\"line-height:0px;font-size:0px;mso-line-height-rule:exactly;\"><![endif]-->"
        "<div style=\"background:#ffffff;background-color:#ffffff;margin:0px auto;max-width:600px;\">"
        "<table align=\"center\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"background:#ffffff;background-color:#ffffff;width:100%;\">"
        "<tbody>"
        "<tr>"
        "<td style=\"direction:ltr;font-size:0px;padding:20px 0;padding-bottom:0px;padding-top:0;text-align:center;\">"
        "<!--[if mso | IE]><table role=\"presentation\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tr><td class=\"\" style=\"vertical-align:top;width:600px;\" ><![endif]-->"
        "<div class=\"mj-column-per-100 mj-outlook-group-fix\" style=\"font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;\">"
        "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"vertical-align:top;\" width=\"100%\">"
        "<tbody>"
        "<tr>"
        "<td align=\"center\" style=\"font-size:0px;padding:10px 25px;padding-top:0;padding-right:0px;padding-bottom:0px;padding-left:0px;word-break:break-word;\">"
        "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"border-collapse:collapse;border-spacing:0px;\">"
        "<tbody>"
        "<tr>"
        "<td style=\"width:600px;\">"
        "<img alt=\"\" height=\"auto\" src=\"https://www.imagecloud.online/images/2023/03/02/LOGO.png\" style=\"border:none;display:block;outline:none;text-decoration:none;height:auto;width:100%;font-size:13px;\" width=\"600\" />"
        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</div>"
        "<!--[if mso | IE]></td></tr></table><![endif]-->"
        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</div>"
        "<!--[if mso | IE]></td></tr></table><table align=\"center\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"\" role=\"presentation\" style=\"width:600px;\" width=\"600\" bgcolor=\"#111111\" ><tr><td style=\"line-height:0px;font-size:0px;mso-line-height-rule:exactly;\"><![endif]-->"
        "<div style=\"background:#111111;background-color:#111111;margin:0px auto;max-width:600px;\">"
        "<table align=\"center\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"background:#111111;background-color:#111111;width:100%;\">"
        "<tbody>"
        "<tr>"
        "<td style=\"direction:ltr;font-size:0px;padding:20px 0;padding-bottom:0px;padding-top:0;text-align:center;\">"
        "<!--[if mso | IE]><table role=\"presentation\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tr><td class=\"\" style=\"vertical-align:top;width:600px;\" ><![endif]-->"
        "<div class=\"mj-column-per-100 mj-outlook-group-fix\" style=\"font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:top;width:100%;\">"
        "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"vertical-align:top;\" width=\"100%\">"
        "<tbody>"
        "<tr>"
        "<td align=\"center\" style=\"font-size:0px;padding:10px 25px;padding-top:50px;padding-right:25px;padding-bottom:30px;padding-left:25px;word-break:break-word;\">"
        "<div style=\"font-family:open Sans Helvetica, Arial, sans-serif;font-size:45px;font-weight:bold;line-height:1;text-align:center;color:#ffffff;\">Welcome to Albedo Hub</div>"
        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</div>"
        "<!--[if mso | IE]></td></tr></table><![endif]-->"
        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</div>"
        "<!--[if mso | IE]></td></tr></table><table align=\"center\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"\" role=\"presentation\" style=\"width:600px;\" width=\"600\" bgcolor=\"#222222\" ><tr><td style=\"line-height:0px;font-size:0px;mso-line-height-rule:exactly;\"><![endif]-->"
        "<div style=\"background:#222222;background-color:#222222;margin:0px auto;max-width:600px;\">"
        "<table align=\"center\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"background:#222222;background-color:#222222;width:100%;\">"
        "<tbody>"
        "<tr>"
        "<td style=\"direction:ltr;font-size:0px;padding:20px 0;padding-bottom:20px;padding-top:20px;text-align:center;\">"
        "<!--[if mso | IE]><table role=\"presentation\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\"><tr><td class=\"\" style=\"vertical-align:middle;width:600px;\" ><![endif]-->"
        "<div class=\"mj-column-per-100 mj-outlook-group-fix\" style=\"font-size:0px;text-align:left;direction:ltr;display:inline-block;vertical-align:middle;width:100%;\">"
        "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" role=\"presentation\" style=\"vertical-align:middle;\" width=\"100%\">"
        "<tbody>"
        "<tr>"
        "<td align=\"left\" style=\"font-size:0px;padding:10px 25px;padding-right:25px;padding-left:25px;word-break:break-word;\">"
        "<div style=\"font-family:open Sans Helvetica, Arial, sans-serif;font-size:22px;line-height:1;text-align:left;color:#ffffff;\"><span style=\"color:#\">Dear "

        // UserName
        "[--------$First$Name$(40Bytes)$--------]"


        "</span><br /><br /> Welcome to Albedo.</div>"
        "</td>"
        "</tr>"
        "<tr>"
        "<td align=\"left\" style=\"font-size:0px;padding:10px 25px;padding-right:25px;padding-left:25px;word-break:break-word;\">"
        "<div style=\"font-family:open Sans Helvetica, Arial, sans-serif;font-size:15px;line-height:1;text-align:left;color:#ffffff;\">"

        // Content
        "We&apos;re really excited you&apos;ve decided to give us a try. "


        "</div>"
        "</td>"
        "</tr>"
        "<tr>"
        "<td align=\"left\" style=\"font-size:0px;padding:10px 25px;word-break:break-word;\">"
        "<div style=\"font-family:open Sans Helvetica, Arial, sans-serif;font-size:22px;font-weight:bold;line-height:1;text-align:left;color:#CC3344;\">Verification Code: "

        // Verification Code
        "$CODE$" // 6Byte


        "</div>"
        "</td>"
        "</tr>"
        "<tr>"
        "<td align=\"left\" style=\"font-size:0px;padding:10px 25px;padding-right:25px;padding-left:25px;word-break:break-word;\">"
        "<div style=\"font-family:open Sans Helvetica, Arial, sans-serif;font-size:15px;line-height:1;text-align:left;color:#ffffff;\">"

        // Tail
        "Please do not reply this auto-generated mail. <br /> www.albedo.cc</div>"


        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</div>"
        "<!--[if mso | IE]></td></tr></table><![endif]-->"
        "</td>"
        "</tr>"
        "</tbody>"
        "</table>"
        "</div>"
        "<!--[if mso | IE]></td></tr></table><![endif]-->"
        "</div>"
        "</body>"
        ""
        "</html>"
        "";
}