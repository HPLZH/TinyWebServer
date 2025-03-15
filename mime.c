#include "global.h"

long long extCode(const char *ext)
{
	if (ext == NULL)
	{
		return 0;
	}
	long long rc = 0;
	strncpy((char *)(&rc), ext, sizeof(rc));
	return rc;
}

const char *mimeType(const char *fn)
{
	const char *pd = strrchr(fn, '/');
	if (pd)
	{
		pd = strchr(pd, '.');
	}
	if (pd)
	{
		pd++;
	}
	long long extc = extCode(pd);
	switch (extc)
	{
	case EXT_html:
	case EXT_htm:
	{
		return HTML;
	}
	case EXT_css:
	{
		return CSS;
	}
	case EXT_js:
	{
		return JAVASCRIPT;
	}
	case EXT_txt:
	{
		return PLAIN_TEXT;
	}
	case EXT_json:
	{
		return JSON;
	}
	case EXT_xml:
	{
		return XML;
	}
	case EXT_zip:
	{
		return ZIP;
	}
	case EXT_7z:
	{
		return Z7;
	}
	case EXT_pdf:
	{
		return PDF;
	}
	case EXT_png:
	{
		return PNG;
	}
	case EXT_ico:
	{
		return ICO;
	}
	case EXT_gif:
	{
		return GIF;
	}
	case EXT_bmp:
	{
		return BMP;
	}
	case EXT_jpeg:
	case EXT_jpg:
	{
		return JPEG;
	}
	case EXT_webp:
	{
		return WEBP;
	}
	case EXT_svg:
	{
		return SVG;
	}
	case EXT_apng:
	{
		return APNG;
	}
	case EXT_weba:
	{
		return WEBA;
	}
	case EXT_mid:
	case EXT_midi:
	{
		return MIDI;
	}
	case EXT_wav:
	{
		return WAV;
	}
	case EXT_mp3:
	{
		return MP3;
	}
	case EXT_aac:
	{
		return AAC;
	}
	case EXT_webm:
	{
		return WEBM;
	}
	case EXT_mp4:
	{
		return MP4;
	}
	case EXT_mpeg:
	{
		return MPEG;
	}
	case EXT_doc:
	{
		return DOC;
	}
	case EXT_docx:
	{
		return DOCX;
	}
	case EXT_ppt:
	{
		return PPT;
	}
	case EXT_pptx:
	{
		return PPTX;
	}
	case EXT_xls:
	{
		return XLS;
	}
	case EXT_xlsx:
	{
		return XLSX;
	}
	case EXT_abw:
	{
		return ABW;
	}
	case EXT_arc:
	{
		return ARC;
	}
	case EXT_bin:
	{
		return BIN;
	}
	case EXT_avif:
	{
		return AVIF;
	}
	case EXT_cda:
	{
		return CDA;
	}
	case EXT_csh:
	{
		return CSH;
	}
	case EXT_csv:
	{
		return CSV;
	}
	case EXT_epub:
	{
		return EPUB;
	}
	case EXT_gz:
	{
		return GZ;
	}
	case EXT_jar:
	{
		return JAR;
	}
	case EXT_mpkg:
	{
		return MPKG;
	}
	case EXT_odp:
	{
		return ODP;
	}
	case EXT_ods:
	{
		return ODS;
	}
	case EXT_odt:
	{
		return ODT;
	}
	case EXT_oga:
	{
		return OGA;
	}
	case EXT_ogv:
	{
		return OGV;
	}
	case EXT_ogx:
	{
		return OGX;
	}
	case EXT_opus:
	{
		return OPUS;
	}
	case EXT_otf:
	{
		return OTF;
	}
	case EXT_php:
	{
		return PHP;
	}
	case EXT_rar:
	{
		return RAR;
	}
	case EXT_rtf:
	{
		return RTF;
	}
	case EXT_sh:
	{
		return SH;
	}
	case EXT_tar:
	{
		return TAR;
	}
	case EXT_tif:
	case EXT_tiff:
	{
		return TIFF;
	}
	case EXT_ts:
	{
		return TS;
	}
	case EXT_ttf:
	{
		return TTF;
	}
	case EXT_vsd:
	{
		return VSD;
	}
	case EXT_woff:
	{
		return WOFF;
	}
	case EXT_xhtml:
	{
		return XHTML;
	}
	case EXT_xul:
	{
		return XUL;
	}
	default:
	{
		return BINARY_DATA;
	}
	}
}
