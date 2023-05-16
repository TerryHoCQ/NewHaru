#include "../include/PdfPage.hpp"
#include "../include/Destination.hpp"
#include "../include/TextAnnotation.hpp"
#include "../include/LinkAnnotation.hpp"
#include "../include/Box.hpp"
#include "../include/Encoder.hpp"
#include "../include/Coor2D.hpp"
#include "../include/Font.hpp"
#include "../include/TransposeMatrix.hpp"
#include "../include/DashMode.hpp"
#include "../include/RGBColor.hpp"
#include "../include/CMYKColor.hpp"
#include "../include/Image.hpp"
using namespace pdf;


ColorSpace convertToColorSpace(HPDF_ColorSpace colorSpace) {
    switch (colorSpace) {
        case HPDF_CS_DEVICE_GRAY: return ColorSpace::DEVICE_GRAY;
        case HPDF_CS_DEVICE_RGB: return ColorSpace::DEVICE_RGB;
        case HPDF_CS_DEVICE_CMYK: return ColorSpace::DEVICE_CMYK;
        case HPDF_CS_CAL_GRAY: return ColorSpace::CAL_GRAY;
        case HPDF_CS_CAL_RGB: return ColorSpace::CAL_RGB;
        case HPDF_CS_LAB: return ColorSpace::LAB;
        case HPDF_CS_ICC_BASED: return ColorSpace::ICC_BASED;
        case HPDF_CS_SEPARATION: return ColorSpace::SEPARATION;
        case HPDF_CS_DEVICE_N: return ColorSpace::DEVICE_N;
        case HPDF_CS_INDEXED: return ColorSpace::INDEXED;
        case HPDF_CS_PATTERN: return ColorSpace::PATTERN;
        default: return ColorSpace::EOF_COLOR_SPACE;
    }
}

PdfPage::PdfPage(const HPDF_Page content): ContentStream(content) {}

void PdfPage::setWidth(float value) {
    HPDF_Page_SetWidth(innerContent, value);
}

void PdfPage::setHeight(float value) {
    HPDF_Page_SetHeight(innerContent, value);
}

void PdfPage::setSize(PageSize size, PageOrientation orientation) {
    HPDF_Page_SetSize(innerContent, (HPDF_PageSizes) size, (HPDF_PageDirection) orientation);
}

void PdfPage::setRotation(PageRotation rotation) {
    HPDF_Page_SetRotate(innerContent, (unsigned short) rotation);
}

float PdfPage::getWidth() const {
    return HPDF_Page_GetWidth(innerContent);
}

float PdfPage::getHeight() const {
    return HPDF_Page_GetHeight(innerContent);
}

Destination PdfPage::createDestination() {
    return Destination(HPDF_Page_CreateDestination(innerContent));
}

TextAnnotation PdfPage::createTextAnnotation(const std::string& text, const Box& box, const Encoder& encoder) {
    return TextAnnotation(HPDF_Page_CreateTextAnnot(innerContent, box.innerContent, text.c_str(), encoder.innerContent));
}

TextAnnotation PdfPage::createTextAnnotation(const std::string& text, const Box& box) {
    return TextAnnotation(HPDF_Page_CreateTextAnnot(innerContent, box.innerContent, text.c_str(), nullptr));
}

LinkAnnotation PdfPage::createLinkAnnotation(const Destination& destination, const Box& box) {
    return LinkAnnotation(HPDF_Page_CreateLinkAnnot(innerContent, box.innerContent, destination.innerContent));
}

LinkAnnotation PdfPage::createURILinkAnnotation(const std::string& uri, const Box& box) {
    return LinkAnnotation(HPDF_Page_CreateURILinkAnnot(innerContent, box.innerContent, uri.c_str()));
}

float PdfPage::getTextWidth(const std::string& text) const {
    return HPDF_Page_TextWidth(innerContent, text.c_str());
}

std::pair<unsigned int, float> PdfPage::measureText(const std::string& text, float width, bool wordWrap) const {
    float realWidth;
    unsigned int val = HPDF_Page_MeasureText(innerContent, text.c_str(), width, wordWrap, &realWidth);
    return {val, realWidth};
}

unsigned short PdfPage::getGMode() const {
    return HPDF_Page_GetGMode(innerContent);
}

Coor2D PdfPage::getCurrentPos() const {
    return Coor2D(HPDF_Page_GetCurrentPos(innerContent));
}

Coor2D PdfPage::getCurrentTextPos() const {
    return Coor2D(HPDF_Page_GetCurrentTextPos(innerContent));
}

Font PdfPage::getCurrentFont() const {
    return Font(HPDF_Page_GetCurrentFont(innerContent));
}

float PdfPage::getCurrentFontSize() const {
    return HPDF_Page_GetCurrentFontSize(innerContent);
}

TransposeMatrix PdfPage::getTransposeMatrix() const {
    return TransposeMatrix(HPDF_Page_GetTransMatrix(innerContent));
}

float PdfPage::getLineWidth() const {
    return HPDF_Page_GetLineWidth(innerContent);
}

LineCap PdfPage::getLineCap() const {
    switch (HPDF_Page_GetLineCap(innerContent)) {
        case HPDF_BUTT_END: return LineCap::BUTT_END;
        case HPDF_ROUND_END: return LineCap::ROUND_END;
        case HPDF_PROJECTING_SQUARE_END: return LineCap::PROJECTING_SQUARE_END;
        default: return LineCap::LINECAP_EOF;
    }
}

LineJoin PdfPage::getLineJoin() const {
    switch (HPDF_Page_GetLineJoin(innerContent)) {
        case HPDF_MITER_JOIN: return LineJoin::MITER_JOIN;
        case HPDF_ROUND_JOIN: return LineJoin::ROUND_JOIN;
        case HPDF_BEVEL_JOIN: return LineJoin::BEVEL_JOIN;
        default: return LineJoin::LINEJOIN_EOF;
    }
}

float PdfPage::getMiterLimit() const {
    return HPDF_Page_GetMiterLimit(innerContent);
}

DashMode PdfPage::getDash() const {
    return DashMode(HPDF_Page_GetDash(innerContent));
}

float PdfPage::getFlatness() const {
    return HPDF_Page_GetFlat(innerContent);
}

float PdfPage::getCharSpace() const {
    return HPDF_Page_GetCharSpace(innerContent);
}

float PdfPage::getWordSpace() const {
    return HPDF_Page_GetWordSpace(innerContent);
}

float PdfPage::getHorizontalScalling() const {
    return HPDF_Page_GetHorizontalScalling(innerContent);
}

float PdfPage::getTextLeading() const {
    return HPDF_Page_GetTextLeading(innerContent);
}

TextRenderingMode PdfPage::getTextRenderingMode() const {
    switch (HPDF_Page_GetTextRenderingMode(innerContent)) {
        case HPDF_FILL: return TextRenderingMode::FILL;
        case HPDF_STROKE: return TextRenderingMode::STROKE;
        case HPDF_FILL_THEN_STROKE: return TextRenderingMode::FILL_THEN_STROKE;
        case HPDF_INVISIBLE: return TextRenderingMode::INVISIBLE;
        case HPDF_FILL_CLIPPING: return TextRenderingMode::FILL_CLIPPING;
        case HPDF_STROKE_CLIPPING: return TextRenderingMode::STROKE_CLIPPING;
        case HPDF_FILL_STROKE_CLIPPING: return TextRenderingMode::FILL_STROKE_CLIPPING;
        case HPDF_CLIPPING: return TextRenderingMode::CLIPPING;
        default: return TextRenderingMode::EOF_MODE;
    }
}

float PdfPage::getTextRise() const {
    return HPDF_Page_GetTextRise(innerContent);
}

RGBColor PdfPage::getRGBFill() const {
    return RGBColor(HPDF_Page_GetRGBFill(innerContent));
}

RGBColor PdfPage::getRGBStroke() const {
    return RGBColor(HPDF_Page_GetRGBStroke(innerContent));
}

CMYKColor PdfPage::getCMYKFill() const {
    return CMYKColor(HPDF_Page_GetCMYKFill(innerContent));
}

CMYKColor PdfPage::getCMYKStroke() const {
    return CMYKColor(HPDF_Page_GetCMYKStroke(innerContent));
}

float PdfPage::getGrayFill() const {
    return HPDF_Page_GetGrayFill(innerContent);
}

float PdfPage::getGrayStroke() const {
    return HPDF_Page_GetGrayStroke(innerContent);
}

ColorSpace PdfPage::getStrokingColorSpace() const {
    return convertToColorSpace(HPDF_Page_GetStrokingColorSpace(innerContent));
}

ColorSpace PdfPage::getFillingColorSpace() const {
    return convertToColorSpace(HPDF_Page_GetFillingColorSpace(innerContent));
}

TransposeMatrix PdfPage::getTextMatrix() const {
    return TransposeMatrix(HPDF_Page_GetTextMatrix(innerContent));
}

unsigned int PdfPage::getGStateDepth() const {
    return HPDF_Page_GetGStateDepth(innerContent);
}

void PdfPage::setSlideShow(TransitionStyle type, float dispTime, float transTime) {
    HPDF_Page_SetSlideShow(innerContent, (HPDF_TransitionStyle) type, dispTime, transTime);
}

void PdfPage::newContentStream(const ContentStream& newStream) {
    HPDF_Page_New_Content_Stream(innerContent, &newStream.innerContent);
}

void PdfPage::insertSharedContentStream(const ContentStream& sharedStream) {
    HPDF_Page_Insert_Shared_Content_Stream(innerContent, sharedStream.innerContent);
}

void PdfPage::arc(const Coor2D& coors, float radius, float ang1, float ang2) {
    HPDF_Page_Arc(innerContent, coors.getX(), coors.getY(), radius, ang1, ang2);
}

void PdfPage::beginText() {
    HPDF_Page_BeginText(innerContent);
}

void PdfPage::circle(const Coor2D& coors, float radius) {
    HPDF_Page_Circle(innerContent, coors.getX(), coors.getY(), radius);
}

void PdfPage::clip() {
    HPDF_Page_Clip(innerContent);
}

void PdfPage::closePath() {
    HPDF_Page_ClosePath(innerContent);
}

void PdfPage::closePathStroke() {
    HPDF_Page_ClosePathStroke(innerContent);
}

void PdfPage::closePathEofillStroke() {
    HPDF_Page_ClosePathEofillStroke(innerContent);
}

void PdfPage::closePathFillStroke() {
    HPDF_Page_ClosePathFillStroke(innerContent);
}

void PdfPage::concat(const TransposeMatrix& matrix) {
    HPDF_Page_Concat(innerContent, matrix.getA(), matrix.getB(), matrix.getC(), matrix.getD(), matrix.getX(), matrix.getY());
}

void PdfPage::curveTo(float x1, float y1, float x2, float y2, float x3, float y3) {
    HPDF_Page_CurveTo(innerContent, x1, y1, x2, y2, x3, y3);
}

void PdfPage::curveTo2(float x2, float y2, float x3, float y3) {
    HPDF_Page_CurveTo2(innerContent, x2, y2, x3, y3);
}

void PdfPage::curveTo3(float x1, float y1, float x3, float y3) {
    HPDF_Page_CurveTo3(innerContent, x1, y1, x3, y3);
}

void PdfPage::drawImage(const Image& image, const Coor2D& coors, float width, float height) {
    HPDF_Page_DrawImage(innerContent, image.innerContent, coors.getX(), coors.getY(), width, height);
}

void PdfPage::ellipse(const Coor2D& coors, float xRadius, float yRadius) {
    HPDF_Page_Ellipse(innerContent, coors.getX(), coors.getY(), xRadius, yRadius);
}

void PdfPage::endPath() {
    HPDF_Page_EndPath(innerContent);
}

void PdfPage::endText() {
    HPDF_Page_EndText(innerContent);
}

void PdfPage::eoClip() {
    HPDF_Page_Eoclip(innerContent);
}

void PdfPage::eoFill() {
    HPDF_Page_Eofill(innerContent);
}

void PdfPage::eoFillStroke() {
    HPDF_Page_EofillStroke(innerContent);
}

void PdfPage::executeContentStream(const ContentStream& stream) {
    HPDF_Page_ExecuteXObject(innerContent, stream.innerContent);
}

void PdfPage::fill() {
    HPDF_Page_Fill(innerContent);
}

void PdfPage::fillStroke() {
    HPDF_Page_FillStroke(innerContent);
}

void PdfPage::gRestore() {
    HPDF_Page_GRestore(innerContent);
}

void PdfPage::gSave() {
    HPDF_Page_GSave(innerContent);
}

void PdfPage::lineTo(const Coor2D& coors) {
    HPDF_Page_LineTo(innerContent, coors.getX(), coors.getY());
}

void PdfPage::moveTextPos(const Coor2D& coors) {
    HPDF_Page_MoveTextPos(innerContent, coors.getX(), coors.getY());
}

void PdfPage::moveTextPos2(const Coor2D& coors) {
    HPDF_Page_MoveTextPos2(innerContent, coors.getX(), coors.getY());
}

void PdfPage::moveTo(const Coor2D& coors) {
    HPDF_Page_MoveTo(innerContent, coors.getX(), coors.getY());
}

void PdfPage::moveToNextLine() {
    HPDF_Page_MoveToNextLine(innerContent);
}

void PdfPage::rectangle(float x, float y, float width, float height) {
    HPDF_Page_Rectangle(innerContent, x, y, width, height);
}

void PdfPage::setCharSpace(float value) {
    HPDF_Page_SetCharSpace(innerContent, value);
}

void PdfPage::setCMYKFill(const CMYKColor& color) {
    HPDF_Page_SetCMYKFill(innerContent, color.getC(), color.getM(), color.getY(), color.getK());
}

void PdfPage::setCMYKStroke(const CMYKColor& color) {
    HPDF_Page_SetCMYKStroke(innerContent, color.getC(), color.getM(), color.getY(), color.getK());
}

void PdfPage::setDash(const DashMode& mode) {
    HPDF_Page_SetDash(innerContent, mode.innerContent.ptn, mode.innerContent.num_ptn, mode.innerContent.phase);
}

void PdfPage::setExternGState(const ContentStream& stream) {
    HPDF_Page_SetExtGState(innerContent, stream.innerContent);
}

void PdfPage::setFontAndSize(const Font& font, float size) {
    HPDF_Page_SetFontAndSize(innerContent, font.innerContent, size);
}

void PdfPage::setGrayFill(float gray) {
    HPDF_Page_SetGrayFill(innerContent, gray);
}

void PdfPage::setGrayStroke(float gray) {
    HPDF_Page_SetGrayStroke(innerContent, gray);
}

void PdfPage::setHorizontalScalling(float value) {
    HPDF_Page_SetHorizontalScalling(innerContent, value);
}

void PdfPage::setLineCap(LineCap lineCap) {
    HPDF_Page_SetLineCap(innerContent, (HPDF_LineCap) lineCap);
}

void PdfPage::setLineJoin(LineJoin lineJoin) {
    HPDF_Page_SetLineJoin(innerContent, (HPDF_LineJoin) lineJoin);
}

void PdfPage::setLineWidth(float lineWidth) {
    HPDF_Page_SetLineWidth(innerContent, lineWidth);
}

void PdfPage::setMiterLimit(float miterLimit) {
    HPDF_Page_SetMiterLimit(innerContent, miterLimit);
}

void PdfPage::setRGBFill(const RGBColor& color) {
    HPDF_Page_SetRGBFill(innerContent, color.getR(), color.getG(), color.getB());
}

void PdfPage::setRGBStroke(const RGBColor& color) {
    HPDF_Page_SetRGBStroke(innerContent, color.getR(), color.getG(), color.getB());
}

void PdfPage::setTextLeading(float value) {
    HPDF_Page_SetTextLeading(innerContent, value);
}

void PdfPage::setTextMatrix(const TransposeMatrix& matrix) {
    HPDF_Page_SetTextMatrix(innerContent, matrix.getA(), matrix.getB(), matrix.getC(), matrix.getD(), matrix.getX(), matrix.getY());
}

void PdfPage::setTextRenderingMode(TextRenderingMode mode) {
    HPDF_Page_SetTextRenderingMode(innerContent, (HPDF_TextRenderingMode) mode);
}

void PdfPage::setTextRise(float value) {
    HPDF_Page_SetTextRise(innerContent, value);
}

void PdfPage::setWordSpace(float value) {
    HPDF_Page_SetWordSpace(innerContent, value);
}

void PdfPage::showText(const std::string& text) {
    HPDF_Page_ShowText(innerContent, text.c_str());
}

void PdfPage::showTextNewLine(const std::string& text) {
    HPDF_Page_ShowTextNextLine(innerContent, text.c_str());
}

void PdfPage::showTextNewLine(float wordSpace, float charSpace, const std::string& text) {
    HPDF_Page_ShowTextNextLineEx(innerContent, wordSpace, charSpace, text.c_str());
}

void PdfPage::stroke() {
    HPDF_Page_Stroke(innerContent);
}

void PdfPage::textOut(const std::string& text, const Coor2D& position) {
    HPDF_Page_TextOut(innerContent, position.getX(), position.getY(), text.c_str());
}

void PdfPage::textOut(const std::string& text) {
    textOut(text, getCurrentTextPos());
}

unsigned int PdfPage::textRect(const Box& box, const std::string& text, TextAlignment alignment) {
    unsigned int length;
    HPDF_Page_TextRect(
        innerContent, box.getLeft(), box.getTop(), box.getRight(), box.getBottom(),
        text.c_str(), (HPDF_TextAlignment) alignment, &length
    );
    return length;
}

void PdfPage::writeText(const std::string& text, const Coor2D& position) {
    beginText();
    textOut(text, position);
    endText();
}

void PdfPage::writeText(const std::string& text) {
    writeText(text, getCurrentTextPos());
}
