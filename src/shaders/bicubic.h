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
outAU4 con4,
outAU4 con5,
outAU4 con6,
outAU4 con7,
outAU4 con8,
outAU4 con9,
// This the rendered image resolution
AF1 inputViewportInPixelsX,
AF1 inputViewportInPixelsY,
// This is the resolution of the resource containing the input image (useful for dynamic resolution)
AF1 inputSizeInPixelsX,
AF1 inputSizeInPixelsY,
// This is the display resolution
AF1 outputSizeInPixelsX,
AF1 outputSizeInPixelsY)
{
 // Input/Output size information
 con0[0]=AU1_AF1(inputViewportInPixelsX*ARcpF1(outputSizeInPixelsX));
 con0[1]=AU1_AF1(inputViewportInPixelsY*ARcpF1(outputSizeInPixelsY));

 con0[2]=AU1_AF1(AF1_(0.5)*inputViewportInPixelsX*ARcpF1(outputSizeInPixelsX)-AF1_(0.5));
 con0[3]=AU1_AF1(AF1_(0.5)*inputViewportInPixelsY*ARcpF1(outputSizeInPixelsY)-AF1_(0.5));
 // Viewport pixel position to normalized image space.
 // This is used to get upper-left of 'F' tap.
 // Centers of gather4, first offset from upper-left of 'F'.
 //          +---+---+---+---+---+---+---+---+
 //          |   |   |   |   |   |   |   |   |
 //          +--(1)--+--(0)--+--(2)--+--(3)--+
 //          | b |   | a |   | c |   | d |   |
 //          +---+---+---+---+---+---+---+---+
 //          |   |   |   |   |   |   |   |   |
 //          +--(4)--+--(5)--+--(6)--+--(7)--+
 //          | e |   | f |   | g |   | h |   |
 //          +---+---+---+---+---+---+---+---+
 //          |   |   |   |   |   |   |   |   |
 //          +--(8)--+--(9)--+--(10)-+--(11)-+
 //          | i |   | j |   | k |   | l |   |
 //          +---+---+---+---+---+---+---+---+
 //          |   |   |   |   |   |   |   |   |
 //          +--(12)-+--(13)-+--(14)-+--(15)-+
 //          | m |   | n |   | o |   | p |   |
 //          +---+---+---+---+---+---+---+---+

 con1[0]=AU1_AF1(ARcpF1(inputSizeInPixelsX));
 con1[1]=AU1_AF1(ARcpF1(inputSizeInPixelsY));


 con2[0]=AU1_AF1(AF1_( 0.5)*ARcpF1(inputSizeInPixelsX));
 con2[1]=AU1_AF1(AF1_( 0.5)*ARcpF1(inputSizeInPixelsY));

 con1[2]=AU1_AF1(AF1_( 0.5)*ARcpF1(inputSizeInPixelsX));
 con1[3]=AU1_AF1(AF1_(-0.5)*ARcpF1(inputSizeInPixelsY));

 con3[2]=AU1_AF1(AF1_(-0.5)*ARcpF1(inputSizeInPixelsX));
 con3[3]=AU1_AF1(AF1_( 0.5)*ARcpF1(inputSizeInPixelsY));

 con4[0]=AU1_AF1(AF1_(-0.5)*ARcpF1(inputSizeInPixelsX));
 con4[1]=AU1_AF1(AF1_(-0.5)*ARcpF1(inputSizeInPixelsY));

 // These are from (0) instead of 'F'.
 // coords for b c d

 con2[2]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsX));
 con2[3]=AU1_AF1(AF1_( 0.0)*ARcpF1(inputSizeInPixelsY));

 con3[0]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsX));
 con3[1]=AU1_AF1(AF1_( 0.0)*ARcpF1(inputSizeInPixelsY));

 // coords for e f g h


 con4[2]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsX));
 con4[3]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsY));

 con5[0]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsX));
 con5[1]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsY));

 // coords for i j k l
 con5[2]=AU1_AF1(AF1_(-2.0)*ARcpF1(inputSizeInPixelsX));
 con5[3]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsY));

 con6[0]=AU1_AF1(AF1_( 0.0)*ARcpF1(inputSizeInPixelsX));
 con6[1]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsY));

 con6[2]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsX));
 con6[3]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsY));

 con7[0]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsX));
 con7[1]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsY));

 // coords for m n o p
 con7[2]=AU1_AF1(AF1_(-2.0)*ARcpF1(inputSizeInPixelsX));
 con7[3]=AU1_AF1(AF1_( 6.0)*ARcpF1(inputSizeInPixelsY));

 con8[0]=AU1_AF1(AF1_( 0.0)*ARcpF1(inputSizeInPixelsX));
 con8[1]=AU1_AF1(AF1_( 6.0)*ARcpF1(inputSizeInPixelsY));

 con8[2]=AU1_AF1(AF1_( 2.0)*ARcpF1(inputSizeInPixelsX));
 con8[3]=AU1_AF1(AF1_( 6.0)*ARcpF1(inputSizeInPixelsY));

 con9[0]=AU1_AF1(AF1_( 4.0)*ARcpF1(inputSizeInPixelsX));
 con9[1]=AU1_AF1(AF1_( 6.0)*ARcpF1(inputSizeInPixelsY));
}
