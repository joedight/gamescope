//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//
//
//                    BICUBIC IMAGE SCALING
//
//
//------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//_____________________________________________________________/\_______________________________________________________________
//==============================================================================================================================
//                                                      CONSTANT SETUP
//==============================================================================================================================
// Call to setup required constant values (works on CPU or GPU).
A_STATIC void BicubicCon(
outAU4 con0,
outAU4 con1,
outAU4 con2,
outAU4 con3,
// This the rendered image resolution being upscaled
AF1 inputViewportInPixelsX,
AF1 inputViewportInPixelsY,
// This is the resolution of the resource containing the input image (useful for dynamic resolution)
AF1 inputSizeInPixelsX,
AF1 inputSizeInPixelsY,
// This is the display resolution which the input image gets upscaled to
AF1 outputSizeInPixelsX,
AF1 outputSizeInPixelsY)
{
 // Output integer position to a pixel position in viewport.
 con0[0]=AU1_AF1(inputViewportInPixelsX*ARcpF1(outputSizeInPixelsX));
 con0[1]=AU1_AF1(inputViewportInPixelsY*ARcpF1(outputSizeInPixelsY));
 con0[2]=AU1_AF1(AF1_(0.5)*inputViewportInPixelsX*ARcpF1(outputSizeInPixelsX)-AF1_(0.5));
 con0[3]=AU1_AF1(AF1_(0.5)*inputViewportInPixelsY*ARcpF1(outputSizeInPixelsY)-AF1_(0.5));
 // Viewport pixel position to normalized image space.
 // This is used to get upper-left of 'F' tap.
 con1[0]=AU1_AF1(ARcpF1(inputSizeInPixelsX));
 con1[1]=AU1_AF1(ARcpF1(inputSizeInPixelsY));
 // Centers of gather4, first offset from upper-left of 'F'.
 //      +---+---+
 //      |   |   |
 //      +--(0)--+
 //      | b | c |
 //  +---F---+---+---+
 //  | e | f | g | h |
 //  +--(1)--+--(2)--+
 //  | i | j | k | l |
 //  +---+---+---+---+
 //      | n | o |
 //      +--(3)--+
 //      |   |   |
 //      +---+---+
 con1[2]=AU1_AF1(AF1_( 1.0)*ARcpF1(inputSizeInPixelsX));
 con1[3]=AU1_AF1(AF1_(-1.0)*ARcpF1(inputSizeInPixelsY));
 // These are from (0) instead of 'F'.
 con2[0]=AU1_AF1(AF1_(-1.0)*ARcpF1(inputSizeInPixelsX));
 con2[1]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsY));
 con2[2]=AU1_AF1(AF1_( 1.0)*ARcpF1(inputSizeInPixelsX));
 con2[3]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsY));
 con3[0]=AU1_AF1(AF1_( 0.0)*ARcpF1(inputSizeInPixelsX));
 con3[1]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsY));
 con3[2]=con3[3]=0;
}
